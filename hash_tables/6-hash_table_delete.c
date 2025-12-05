#include "hash_tables.h"
#include <stdlib.h> 

/**
 * hash_table_delete - delete a hash table and free all memory
 * @ht: pointer to the hash table
 *
 * Description:
 * Frees every node, its key, and its value in each bucket,
 * then frees the array and the table itself. If @ht is NULL,
 * nothing happens.
 */
void hash_table_delete(hash_table_t *ht)
{
	unsigned long int i;
	hash_node_t *node, *next;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node != NULL)
		{
			next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			node = next;
		}
	}

	free(ht->array);
	free(ht);
}

