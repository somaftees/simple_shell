#include "main.h"

/**
 * _strcat - concatenate str
 * @dest: char pointer
 * @src: const char
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string
 * @dest: Type char pointer
 * @src: Type char pointer
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{

	size_t counter;

	for (counter = 0; src[counter] != '\0'; counter++)
	{
		dest[counter] = src[counter];
	}
	dest[counter] = '\0';

	return (dest);
}
/**
 * _strcmp - Function compares
 * @s1: type str
 * @s2: type str
 * Return: 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locates
 * @s: string.
 * @c: character.
 * Return: the pointer to the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets the length
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number
 */
int _strspn(char *s, char *accept)
{
	int i, j, b;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		b = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				b = 0;
				break;
			}
		}
		if (b == 1)
			break;
	}
	return (i);
}
