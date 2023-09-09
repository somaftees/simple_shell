#include "main.h"

/**
 * get_len - a function that gets the lenght of a number.
 * @n: integer.
 * Return: len.
 */

int get_len(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		len++;
		n1 = n1 / 10;
	}

	return (len);
}

/**
 * aux_itoa - a function converts int to string.
 * @n: integer.
 * Return: b or NULL.	
 */

char *aux_itoa(int n)
{
	unsigned int n1;
	int len = get_len(n);
	char *b;

	b = malloc(sizeof(char) * (len + 1));
	if (b == 0)
		return (NULL);

	*(b + len) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		b[0] = '-';
	}
	else
	{
		n1 = n;
	}

	len--;
	do {
		*(b + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	}
	while (n1 > 0)
		;
	return (b);
}

/**
 * _atoi - a function that converts a string to an integer.
 * @s: char.
 * Return: value.
 */

int _atoi(char *s)
{
	unsigned int counter = 0, size = 0, h = 0, y = 1, t = 1, i;

	while (*(s + counter) != '\0')
	{
		if (size > 0 && (*(s + counter) < '0' || *(s + counter) > '9'))
			break;

		if (*(s + counter) == '-')
			y *= -1;

		if ((*(s + counter) >= '0') && (*(s + counter) <= '9'))
		{
			if (size > 0)
				t *= 10;
			size++;
		}
		counter++;
	}

	for (i = counter - size; i < counter; i++)
	{
		h = h + ((*(s + i) - 48) * t);
		t /= 10;
	}
	return (h * y);
}
