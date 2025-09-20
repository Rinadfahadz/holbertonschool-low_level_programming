#include <stdlib.h>
#include "dog.h"

/**
 * _strlen - returns the length of a string
 * @s: string
 *
 * Return: length
 */
int _strlen(char *s)
{
	int i = 0;

	if (s == NULL)
		return (0);

	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * _strcpy - copies a string into dest
 * @dest: destination
 * @src: source
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * new_dog - creates a new dog (allocates memory)
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 *
 * Return: pointer to the new dog, or NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	char *name_copy = NULL;
	char *owner_copy = NULL;
	int len;

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	len = _strlen(name);
	if (len > 0)
	{
		name_copy = malloc(len + 1);
		if (!name_copy)
		{
			free(dog);
			return (NULL);
		}
		_strcpy(name_copy, name);
		dog->name = name_copy;
	}
	else
		dog->name = NULL;

	dog->age = age;

