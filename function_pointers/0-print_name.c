#include "function_pointers.h"

/**
 * print_name - calls a function to print a name
 * @name: string name
 * @f: function pointer to print function
 */
void print_name(char *name, void (*f)(char *))
{
	if (name && f)
		f(name);
}

