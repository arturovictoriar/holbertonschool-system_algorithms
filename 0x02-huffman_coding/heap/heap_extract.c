#include "heap.h"

/**
 * heapify - fix the heap_min
 * @heap: heap struct
 * Return: Nothing
 */
void heapify(heap_t *heap)
{
	binary_tree_node_t *node = heap->root, *child = NULL;
	void *temp = NULL;

	while (1)
	{
		if (!node->left)
			break;
		if (!node->right)
			child = node->left;
		else
		{
			if (heap->data_cmp(node->left->data, node->right->data) <= 0)
				child = node->left;
			else
				child = node->right;
		}
		if (heap->data_cmp(node->data, child->data) < 0)
			break;
		temp = node->data, node->data = child->data, child->data = temp;
		node = child;
	}
}

/**
 * get_last_node - get the last node in heap_min
 * @heap: heap struct
 * Return: last node in heap_min
 */
binary_tree_node_t *get_last_node(heap_t *heap)
{
	binary_tree_node_t *node = NULL;
	size_t node_level = 0;

	for (node_level = 1; node_level <= heap->size; node_level <<= 1)
		;
	node_level >>= 2;


	for (node = heap->root; node_level > 0; node_level >>= 1)
	{
		if (heap->size & node_level)
			node = node->right;
		else
			node = node->left;
	}

	return (node);
}

/**
 * heap_extract - extract the head heap_min
 * @heap: heap struct
 * Return: xtracted node's data
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *node = NULL;
	void *data = NULL;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;
	if (heap->size == 1)
		return (free(heap->root), heap->root = NULL, --heap->size, data);

	node = get_last_node(heap);

	heap->root->data = node->data;
	if (node->parent->left == node)
		node->parent->left = NULL;
	else
		node->parent->right = NULL;

	--heap->size, free(node), heapify(heap);
	return (data);
}
