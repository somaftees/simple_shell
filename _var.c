#include "main.h"

/**
 * check_env - a function that checks if the
 * typed variable is an env variable.
 * @h: r_var.
 * @in: a char.
 * @data: data_shell.
 * Return: void.
 */

void check_env(r_var **h, char *in, data_shell *data)
{
	int i, cha, j, t;
	char **e;

	e = data->_environ;
	for (i = 0; e[i]; i++)
	{
		for (j = 1, cha = 0; e[i][cha]; cha++)
		{
			if (e[i][cha] == '=')
			{
				t = _strlen(e[i] + cha + 1);
				add_rvar_node(h, j, e[i] + cha + 1, t);
				return;
			}

			if (in[j] == e[i][cha])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - a function that checks if
 * the typed variable is $$ or $?
 * @h: r_var.
 * @in: a char.
 * @st: a char.
 * @data: data_shell.
 * Return: void.
 */

int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int i, last, p;

    p = _strlen(data->pid);
	last = _strlen(st);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(h, 2, st, last), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, p), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_input - a function that replaces string into variables.
 * @head: r_var.
 * @input: a char.
 * @new_input: a char.
 * @nlen: a char.
 * Return: new_input.
 */

char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *index;
	int i, j, m;

	index = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (m = 0; m < index->len_var; m++)
					j++;
				i--;
			}
			else
			{
				for (m = 0; m < index->len_val; m++)
				{
					new_input[i] = index->val[m];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - a function that calls functions
 * to replace string into vars.
 * @input: a char.
 * @datash: data_shell
 * Return: new_input.
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *h, *index;
	char *s, *new_input;
	int ol, nl;

	s = aux_itoa(datash->s);
	h = NULL;

	ol = check_vars(&h, input, s, datash);

	if (h == NULL)
	{
		free(s);
		return (input);
	}

	index = h;
	nl = 0;

	while (index != NULL)
	{
		nl += (index->len_val - index->len_var);
		index = index->next;
	}

	nl += ol;

	new_input = malloc(sizeof(char) * (nl + 1));
	new_input[nl] = '\0';

	new_input = replaced_input(&h, input, new_input, nlen);

	free(input);
	free(s);
	free_rvar_list(&h);

	return (new_input);
}
