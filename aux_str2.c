#include "main.h"

/**
 * _strdup - duplicates str
 * @s: Type char
 * Return: duplicated
 */
char *_strdup(const char *s)
{
	char *new_var;
	size_t length;

	length = _strlen(s);
	new_var = malloc(sizeof(char) * (length + 1));
	if (new_var == NULL)
		return (NULL);
	_memcpy(new_var, s, length + 1);
	return (new_var);
}

/**
 * _strlen - Returns the lenght
 * @s: Type
 * Return: only 0
 */
int _strlen(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars - compare
 * @str: input
 * @delim: delimiter
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *s_plit, *s_end;
	char *s_start;
	unsigned int i, b;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		s_plit = str; /*Store first address*/
		i = _strlen(str);
		s_end = &str[i]; /*Store last address*/
	}
	s_start = s_plit;
	if (s_start == s_end) /*Reaching the end*/
		return (NULL);

	for (b = 0; *s_plit; s_plit++)
	{
		/*Breaking loop finding the next token*/
		if (s_plit != s_start)
			if (*s_plit && *(s_plit - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*s_plit == delim[i])
			{
				*s_plit = '\0';
				if (s_plit == s_start)
					s_start++;
				break;
			}
		}
		if (b == 0 && *s_plit) /*Str != Delim*/
			b = 1;
	}
	if (b == 0) /*Str == Delim*/
		return (NULL);
	return (s_start);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
