#include "main.h"

/**
 * puts_half - prints the second half of a string
 * @str: pointer to the string
 *
 * Description: prints characters starting from the middle of the string
 * to the end, followed by a new line. If the length is odd, prints
 * the last (length + 1) / 2 characters.
 */
void puts_half(char *str)
{
	int len = 0;
	int start;
	int i;

	/* find the length of the string */
	while (str[len] != '\0')
		len++;

	/* determine the starting index */
	if (len % 2 == 0)
		start = len / 2;
	else
		start = (len + 1) / 2;

	/* print from start to end */
	for (i = start; i < len; i++)
		_putchar(str[i]);

	_putchar('\n');
}

