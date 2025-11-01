#include "hash_tables.h"
#include <stdio.h>

/**
 * hash_table_print - print all key/value pairs of a hash table
 * @ht: pointer to the hash table
 *
 * Description:
 * Prints pairs in the order they appear in the array, then along the
 * linked list at each index. If @ht is NULL, nothing is printed.
 */
void hash_table_print(const hash_table_t *ht)
{
	unsigned long int i;
	hash_node_t *node;
	int first = 1;

	if (ht == NULL)
		return;

	printf("{");

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node != NULL)
		{
			if (!first)
				printf(", ");
			printf("'%s': '%s'", node->key, node->value);
			first = 0;
			node = node->next;
		}
	}

	printf("}\n");
}

