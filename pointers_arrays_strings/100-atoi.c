#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: pointer to the string
 *
 * Return: the integer value represented by the string
 *
 * Description:
 * - ignores all characters before the number
 * - considers all '+' and '-' signs before the number
 * - returns 0 if no digits found
 */
int _atoi(char *s)
{
	int i = 0, sign = 1;
	int result = 0;
	int found_digit = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] == '+')
			;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			found_digit = 1;
			break;
		}
		else if (found_digit)
			break;
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		if (sign == 1)
			result = result * 10 + (s[i] - '0');
		else
			result = result * 10 - (s[i] - '0');
		i++;
	}

	return (result);
}
