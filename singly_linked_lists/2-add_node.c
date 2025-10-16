#include "lists.h"
#include <stdlib.h>
#include <string.h>

/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: double pointer to the head of the list
 * @str: string to be duplicated and added
 *
 * Return: address of the new element, or NULL if it failed
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;
	unsigned int len = 0;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);

	if (str != NULL)
	{
		new->str = strdup(str);
		if (new->str == NULL)
		{
			free(new);
			return (NULL);
		}
		while (str[len])
			len++;
		new->len = len;
	}
	else
	{
		new->str = NULL;
		new->len = 0;
	}

	new->next = *head;
	*head = new;

	return (new);
}

