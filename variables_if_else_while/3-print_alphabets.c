#include <stdio.h>

/**
 * main - prints alphabet in lowercase then uppercase
 *
 * Description: just printing a-z then A-Z
 * and finishing with a new line
 *
 * Return: 0
 */
int main(void)
{
	char ch;

	for (ch = 'a'; ch <= 'z'; ch++)
		putchar(ch);

	for (ch = 'A'; ch <= 'Z'; ch++)
		putchar(ch);

	putchar('\n');

	return (0);
}
