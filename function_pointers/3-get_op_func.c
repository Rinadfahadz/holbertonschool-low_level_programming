#include "3-calc.h"
#include <stddef.h>

/**
 * get_op_func - select the correct operation
 * @s: operator string
 *
 * Return: pointer to matching function or NULL
 */
int (*get_op_func(char *s))(int, int)
{
	op_t ops[] = {
		{"+", op_add},
		{"-", op_sub},
		{"*", op_mul},
		{"/", op_div},
		{"%", op_mod},
		{NULL, NULL}
	};
	int i = 0;

	while (ops[i].op)
	{
		if (s[1] == '\0' && *(ops[i].op) == *s)
			return (ops[i].f);
		i++;
	}
	return (NULL);
}

