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

	if (!s)
		return (0);

	while (s[i])
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
 * @name: dog's name
 * @age: dog's age
 * @owner: dog's owner
 *
 * Return: pointer to new dog, NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	char *name_copy;
	char *owner_copy;
	int len;

	dog = malloc(sizeof(dog_t));
	if (!dog)
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

	len = _strlen(owner);
	if (len > 0)
	{
		owner_copy = malloc(len + 1);
		if (!owner_copy)
		{
			free(dog->name);
			free(dog);
			return (NULL);
		}
		_strcpy(owner_copy, owner);
		dog->owner = owner_copy;
	}
	else
		dog->owner = NULL;

	return (dog);
}

