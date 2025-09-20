#include <stdlib.h>
#include <string.h>
#include "dog.h"

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
	char *name_copy, *owner_copy;

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	if (name != NULL)
	{
		name_copy = malloc(strlen(name) + 1);
		if (name_copy == NULL)
		{
			free(dog);
			return (NULL);
		}
		strcpy(name_copy, name);
		dog->name = name_copy;
	}
	else
		dog->name = NULL;

	dog->age = age;

	if (owner != NULL)
	{
		owner_copy = malloc(strlen(owner) + 1);
		if (owner_copy == NULL)
		{
			free(dog->name);
			free(dog);
			return (NULL);
		}
		strcpy(owner_copy, owner);
		dog->owner = owner_copy;
	}
	else
		dog->owner = NULL;

	return (dog);
}
