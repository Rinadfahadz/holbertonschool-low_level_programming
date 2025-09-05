#include "main.h"

/**
 * puts2 - prints every other character of a string
 * @str: pointer to the string
 *
 * Description: prints characters starting with the first one,
 * then every second character until the end of the string,
 * followed by a new line.
 */
void puts2(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i += 2;
	}
	_putchar('\n');
}
