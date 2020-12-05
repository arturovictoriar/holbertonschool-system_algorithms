#include "heap.h"

/**
* heap_create - Create a heap node
* @data_cmp: function pointer to compare a value
* Return: Pointer to the new heap node, NULL otherwise
*/
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new_node = NULL;

	new_node = malloc(sizeof(heap_t));
	if (!new_node)
		return (NULL);

	new_node->size = 0;
	new_node->data_cmp = data_cmp;
	new_node->root = NULL;

	return (new_node);
}
