#include "main.h"

/**
 * add_sep_node_end - adds a separator node
 * @head: head
 * @sep: separator.
 * Return: address
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new_item, *bowl;

	new_item = malloc(sizeof(sep_list));
	if (new_item == NULL)
		return (NULL);

	new_item->separator = sep;
	new_item->next = NULL;
	bowl = *head;

	if (bowl == NULL)
	{
		*head = new_item;
	}
	else
	{
		while (bowl->next != NULL)
			bowl = bowl->next;
		bowl->next = new_item;
	}

	return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: head
 * Return: no
 */
void free_sep_list(sep_list **head)
{
	sep_list *bowl;
	sep_list *c_item;

	if (head != NULL)
	{
		c_item = *head;
		while ((bowl = c_item) != NULL)
		{
			c_item = c_item->next;
			free(bowl);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds a command
 * @head: head
 * @line: command line.
 * Return: address
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new_item, *bowl;

	new_item = malloc(sizeof(line_list));
	if (new_item == NULL)
		return (NULL);

	new_item->line = line;
	new_item->next = NULL;
	bowl = *head;

	if (bowl == NULL)
	{
		*head = new_item;
	}
	else
	{
		while (bowl->next != NULL)
			bowl = bowl->next;
		bowl->next = new_item;
	}

	return (*head);
}

/**
 * free_line_list - frees a line_list
 * @head: head
 * Return: no
 */
void free_line_list(line_list **head)
{
	line_list *bowl;
	line_list *c_item;

	if (head != NULL)
	{
		c_item = *head;
		while ((bowl = c_item) != NULL)
		{
			c_item = c_item->next;
			free(bowl);
		}
		*head = NULL;
	}
}
