#include "function_pointers.h"

/**
 * int_index - searches for an integer using a cmp function
 * @array: array of integers
 * @size: number of elements
 * @cmp: function pointer to compare values
 * Return: index of first match, or -1 if none or size <= 0
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (!array || !cmp || size <= 0)
		return (-1);

	for (i = 0; i < size; i++)
		if (cmp(array[i]))
			return (i);

	return (-1);
}

