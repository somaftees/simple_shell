#include "main.h"

/**
 * rev_string - function reverses string
 * @s: input
 * Return: no
 */
void rev_string(char *s)
{
	int counter = 0, i, j;
	char *string_s, bowl;

	while (counter >= 0)
	{
		if (s[counter] == '\0')
			break;
		counter++;
	}
	string_s = s;

	for (i = 0; i < (counter - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			bowl = *(string_s + j);
			*(string_s + j) = *(string_s + (j - 1));
			*(string_s + (j - 1)) = bowl;
		}
	}
}
