#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_all - prints anything
 * @format: list of types of arguments
 */
void print_all(const char * const format, ...)
{
	va_list args;
	unsigned int i = 0;
	char *sep = "";
	char *str;

	va_start(args, format);
	if (format) /* if#1 */
		while (format[i])
		{
			if (format[i] == 'c' || format[i] == 'i' ||
			    format[i] == 'f' || format[i] == 's') /* if#2 */
			{
				if (format[i] == 'c')
					printf("%s%c", sep, va_arg(args, int));
				if (format[i] == 'i')
					printf("%s%d", sep, va_arg(args, int));
				if (format[i] == 'f')
					printf("%s%f", sep, va_arg(args, double));
				if (format[i] == 's')
				{
					str = va_arg(args, char *);
					str = str ? str : "(nil)";
					printf("%s%s", sep, str);
				}
				sep = ", ";
			}
			i++;
		}
	va_end(args);
	printf("\n");
}

