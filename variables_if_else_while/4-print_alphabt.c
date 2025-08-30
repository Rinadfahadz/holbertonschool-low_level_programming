#include <stdio.h>

/**
 * main - prints alphabet in lowercase except q and e
 *
 * Description: simple loop to print a-z but skipping q and e.
 *
 * Return: 0
 */
int main(void)
{
	char ch;

	for (ch = 'a'; ch <= 'z'; ch++)
	{
		if (ch != 'q' && ch != 'e')
			putchar(ch);
	}

	putchar('\n');

	return (0);
}
