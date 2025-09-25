#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

typedef void (*printer_t)(va_list);

/**
 * print_char - prints a char from va_list
 * @args: va_list containing the char
 */
void print_char(va_list args)
{
	printf("%c", va_arg(args, int));
}

/**
 * print_int - prints an int from va_list
 * @args: va_list containing the int
 */
void print_int(va_list args)
{
	printf("%d", va_arg(args, int));
}

/**
 * print_float - prints a float from va_list
 * @args: va_list containing the double
 */
void print_float(va_list args)
{
	printf("%f", va_arg(args, double));
}

/**
 * print_string - prints a string from va_list
 * @args: va_list containing the string
 */
void print_string(va_list args)
{
	char *s = va_arg(args, char *);

	printf("%s", s ? s : "(nil)");
}

/**
 * print_all - prints anything
 * @format: list of types
 */
void print_all(const char * const format, ...)
{
	va_list args;
	unsigned int i = 0;
	char *sep = "";
	char *types = "cifs";
	printer_t funcs[4] = {print_char, print_int, print_float, print_string};

	va_start(args, format);

	if (format) /* if#1 */
		while (format[i])
		{
			unsigned int j = 0;

			while (j < 4)
			{
				if (format[i] == types[j]) /* if#2 */
				{
					printf("%s", sep);
					funcs[j](args);
					sep = ", ";
					break;
				}
				j++;
			}
			i++;
		}

	va_end(args);
	printf("\n");
}

