#include <stdio.h>

/**
 * main - prints all single-digit numbers separated by comma and space
 *
 * Return: 0
 */
int main(void)
{
	int i;

	for (i = 0; i < 10; i++)
	{
		putchar(i + '0');
		if ((i + 1) % 10 != 0)
		{
			putchar(',');
			putchar(' ');
		}
	}
	putchar('\n');

	return (0);
}
