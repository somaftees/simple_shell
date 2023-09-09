#include "main.h"

/**
 * swap_char - swaps
 * @input: input
 * @bool: type
 * Return: swapped
 */
char *swap_char(char *input, int bool)
{
	int counter;

	if (bool == 0)
	{
		for (counter = 0; input[counter]; counter++)
		{
			if (input[counter] == '|')
			{
				if (input[counter + 1] != '|')
					input[counter] = 16;
				else
					counter++;
			}

			if (input[counter] == '&')
			{
				if (input[counter + 1] != '&')
					input[counter] = 12;
				else
					counter++;
			}
		}
	}
	else
	{
		for (counter = 0; input[counter]; counter++)
		{
			input[counter] = (input[counter] == 16 ? '|' : input[counter]);
			input[counter] = (input[counter] == 12 ? '&' : input[counter]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators
 * @head_s: head
 * @head_l: head commands
 * @input: input string
 * Return: no
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int counter;
	char *lines_of;

	input = swap_char(input, 0);

	for (counter = 0; input[counter]; counter++)
	{
		if (input[counter] == ';')
			add_sep_node_end(head_s, input[counter]);

		if (input[counter] == '|' || input[counter] == '&')
		{
			add_sep_node_end(head_s, input[counter]);
			counter++;
		}
	}

	lines_of = _strtok(input, ";|&");
	do {
		lines_of = swap_char(lines_of, 1);
		add_line_node_end(head_l, lines_of);
		lines_of = _strtok(NULL, ";|&");
	} while (lines_of != NULL);

}

/**
 * go_next - go next command
 * @list_s: separator
 * @list_l: command
 * @datash: data structure of shell
 * Return: no
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int l_sep;
	sep_list *lss;
	line_list *lsl;

	l_sep = 1;
	lss = *list_s;
	lsl = *list_l;

	while (lss != NULL && l_sep)
	{
		if (datash->status == 0)
		{
			if (lss->separator == '&' || lss->separator == ';')
				l_sep = 0;
			if (lss->separator == '|')
				lsl = lsl->next, lss = lss->next;
		}
		else
		{
			if (lss->separator == '|' || lss->separator == ';')
				l_sep = 0;
			if (lss->separator == '&')
				lsl = lsl->next, lss = lss->next;
		}
		if (lss != NULL && !l_sep)
			lss = lss->next;
	}

	*list_s = lss;
	*list_l = lsl;
}

/**
 * split_commands - splits
 * @datash: data
 * @input: input
 * Return: 0 or 1
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *h_s, *li_s;
	line_list *h_l, *li_l;
	int l;

	h_s = NULL;
	h_l = NULL;

	add_nodes(&h_s, &h_l, input);

	li_s = h_s;
	li_l = h_l;

	while (li_l != NULL)
	{
		datash->input = li_l->line;
		datash->args = split_line(datash->input);
		l = exec_line(datash);
		free(datash->args);

		if (l == 0)
			break;

		go_next(&li_s, &li_l, datash);

		if (li_l != NULL)
			li_l = li_l->next;
	}

	free_sep_list(&h_s);
	free_line_list(&h_l);

	if (l == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes
 * @input: input
 * Return: string
 */
char **split_line(char *input)
{
	size_t b_s;
	size_t i;
	char **ts;
	char *t;

	b_s = TOK_BUFSIZE;
	ts = malloc(sizeof(char *) * (b_s));
	if (ts == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	t = _strtok(input, TOK_DELIM);
	ts[0] = t;

	for (i = 1; t != NULL; i++)
	{
		if (i == b_s)
		{
			b_s += TOK_BUFSIZE;
			ts = _reallocdp(ts, i, sizeof(char *) * b_s);
			if (ts == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		t = _strtok(NULL, TOK_DELIM);
		ts[i] = t;
	}

	return (ts);
}
