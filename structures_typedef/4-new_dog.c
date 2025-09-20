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
    unsigned int i, len_name, len_owner;

    d = malloc(sizeof(dog_t));
    if (d == NULL)
        return (NULL);

    len_name = strlen(name);
    len_owner = strlen(owner);

    d->name = malloc(len_name + 1);
    d->owner = malloc(len_owner + 1);
    if (d->name == NULL || d->owner == NULL)
    {
        free(d->name);
        free(d->owner);
        free(d);
        return (NULL);
    }

    for (i = 0; i < len_name; i++)
        d->name[i] = name[i];
    d->name[len_name] = '\0';

    for (i = 0; i < len_owner; i++)
        d->owner[i] = owner[i];
    d->owner[len_owner] = '\0';

    d->age = age;

    return (d);
}

