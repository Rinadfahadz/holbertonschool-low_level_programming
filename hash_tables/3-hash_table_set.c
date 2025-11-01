#include "hash_tables.h"
#include <string.h>

/**
 * create_node - creates a new hash node
 * @key: key string (already validated)
 * @value: value string
 *
 * Return: pointer to the new node, or NULL on failure
 */
hash_node_t *create_node(const char *key, const char *value)
{
	hash_node_t *node;
	char *kdup, *vdup;

	kdup = strdup(key);
	if (kdup == NULL)
		return (NULL);

	if (value == NULL)
		vdup = strdup("");
	else
		vdup = strdup(value);

	if (vdup == NULL)
	{
		free(kdup);
		return (NULL);
	}

	node = malloc(sizeof(hash_node_t));
	if (node == NULL)
	{
		free(kdup);
		free(vdup);
		return (NULL);
	}

	node->key = kdup;
	node->value = vdup;
	node->next = NULL;
	return (node);
}

/**
 * hash_table_set - adds or updates an element in the hash table
 * @ht: pointer to the hash table
 * @key: key string (must not be empty)
 * @value: value string to store
 *
 * Return: 1 on success, 0 on failure
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int idx;
	hash_node_t *node, *cur;

	if (ht == NULL || key == NULL || *key == '\0')
		return (0);

	idx = key_index((const unsigned char *)key, ht->size);
	cur = ht->array[idx];

	while (cur != NULL)
	{
		if (strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = strdup(value ? value : "");
			if (cur->value == NULL)
				return (0);
			return (1);
		}
		cur = cur->next;
	}

	node = create_node(key, value);
	if (node == NULL)
		return (0);

	node->next = ht->array[idx];
	ht->array[idx] = node;

	return (1);
}

