#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * new_dog - creates a new dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 *
 * Return: pointer to the new dog, NULL if it fails
 */
dog_t *new_dog(char *name, float age, char *owner)
{
    dog_t *d;
    char *name_copy, *owner_copy;

    /* allocate memory for struct dog */
    d = malloc(sizeof(dog_t));
    if (d == NULL)
        return (NULL);

    /* allocate memory for name and owner copies */
    name_copy = strdup(name);
    owner_copy = strdup(owner);
    if (name_copy == NULL || owner_copy == NULL)
    {
        free(name_copy);
        free(owner_copy);
        free(d);
        return (NULL);
    }

    /* assign values */
    d->name = name_copy;
    d->age = age;
    d->owner = owner_copy;

    return (d);
}

