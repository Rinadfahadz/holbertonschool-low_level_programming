#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 *           which contains a copy of the string given as a parameter
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL if str is NULL or if
 *         memory allocation fails
 */
char *_strdup(char *str)
{
	char *dup;
	unsigned int i, len = 0;

	if (str == NULL)
		return (NULL);

	/* احسب طول السلسلة */
	while (str[len] != '\0')
		len++;

	/* احجز الذاكرة: طول السلسلة + 1 للـ null terminator */
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	/* انسخ الأحرف */
	for (i = 0; i < len; i++)
		dup[i] = str[i];
	dup[len] = '\0';

	return (dup);
}

