#include "main.h"

/**
 * rev_string - reverses a string in place
 * @s: pointer to the string
 */
void rev_string(char *s)
{
	int len = 0;
	int i;
	char temp;

	/* find the length of the string */
	while (s[len] != '\0')
		len++;

	/* swap characters from both ends */
	for (i = 0; i < len / 2; i++)
	{
		temp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
	}
}
