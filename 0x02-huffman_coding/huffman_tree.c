#include "huffman.h"

/**
 * huffman_tree - create a tree using the huffman algo
 * @data: is a pointer to the priority queue to extract from
 * @freq: is an array containing the associated frequencies
 * @size: lenght of the previous arrays
 * Return: pointer to the root node of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *new_heap = NULL;
	binary_tree_node_t *root = NULL;

	setbuf(stdout, NULL);
	new_heap = huffman_priority_queue(data, freq, size);
	if (!new_heap)
		return (NULL);

	while (new_heap->root && new_heap->size > 1)
	{
		if (!huffman_extract_and_insert(new_heap))
			return (NULL);
	}

	if (new_heap->root)
	{
		root = (binary_tree_node_t *) new_heap->root->data;
		free(new_heap->root);
		free(new_heap);
		return (root);
	}

	return (NULL);
}
