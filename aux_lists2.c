#include "main.h"

/**
 * add_rvar_node - adds var to ls
 * @head: head
 * @lvar: length
 * @val: value
 * @lval: length
 * Return: address
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new_pos, *bowl;

	new_pos = malloc(sizeof(r_var));
	if (new_pos == NULL)
		return (NULL);

	new_pos->len_var = lvar;
	new_pos->val = val;
	new_pos->len_val = lval;

	new_pos->next = NULL;
	bowl = *head;

	if (bowl == NULL)
	{
		*head = new_pos;
	}
	else
	{
		while (bowl->next != NULL)
			bowl = bowl->next;
		bowl->next = new_pos;
	}

	return (*head);
}

/**
 * free_rvar_list - free list
 * @head: head
 * Return: no
 */
void free_rvar_list(r_var **head)
{
	r_var *bowl;
	r_var *curr_pos;

	if (head != NULL)
	{
		curr_pos = *head;
		while ((bowl = curr_pos) != NULL)
		{
			curr_pos = curr_pos->next;
			free(bowl);
		}
		*head = NULL;
	}
}
