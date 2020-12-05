#include "huffman.h"
/**
* free_data - delete a set of structures
* @data: data to delete
* Return: Nothing
*/
void free_data(void *data)
{
	binary_tree_node_t *node = NULL;

	node = (binary_tree_node_t *) data;
	if (!node)
		return;
	if (node->data)
		free(node->data);
	free(node);
}

/**
* data_cmp_huffman - get the subtration of data1 - data2
* @data1: void pointer which store the data of the node1
* @data2: void pointer which store the data of the node2
* Return: the subtration of data1 - data2
*/
int data_cmp_huffman(void *data1, void *data2)
{
	size_t f1 = 0, f2 = 0;
	binary_tree_node_t *data_node1 = NULL, *data_node2 = NULL;

	data_node1 = (binary_tree_node_t *) data1;
	data_node2 = (binary_tree_node_t *) data2;

	if ((!data_node1 && data_node2) ||
		(data_node1 && !data_node1->data && data_node2 && data_node2->data))
		return (-1);
	else if ((data_node1 && !data_node2) ||
		(data_node1 && data_node1->data && data_node2 && !data_node2->data))
		return (1);
	else if ((!data_node1 && !data_node2) ||
		(data_node1 && !data_node1->data && data_node2 && !data_node2->data))
		return (0);

	f1 = ((symbol_t *)data_node1->data)->freq;
	f2 = ((symbol_t *)data_node2->data)->freq;

	return (f1 - f2);
}

/**
* huffman_priority_queue - creates a priority queue(min_heap) tree
* @data: is an array of characters
* @freq: is an array containing the associated frequencies
* @size: lenght of the previous arrays
* Return: pointer to the created priority queue, or NULL otherwise
*/
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	size_t i = 0;
	symbol_t *new_symbol = NULL;
	heap_t *new_heap = NULL;
	binary_tree_node_t *new_node = NULL, *node_inserted = NULL;

	if (!data || !freq)
		return (NULL);

	new_heap = heap_create(data_cmp_huffman);
	if (!new_heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		new_symbol = symbol_create(data[i], freq[i]);
		if (!new_symbol)
			return (heap_delete(new_heap, free_data), NULL);

		new_node = binary_tree_node(NULL, new_symbol);
		if (!new_node)
			return (free(new_symbol), heap_delete(new_heap, free_data), NULL);

		node_inserted = heap_insert(new_heap, (void *) new_node);
		if (!node_inserted)
			return (free_data(new_node), heap_delete(new_heap, free_data), NULL);
	}

	return (new_heap);
}
