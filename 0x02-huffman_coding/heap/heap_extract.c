#include "heap.h"

/**
 * heapify_down - fix the heap_min
 * @heap: heap struct
 * Return: Nothing
 */
void heapify_down(heap_t *heap)
{
	binary_tree_node_t *node = heap->root, *child;
	void *temp;

	while (1)
	{
		if (!node->left)
			break;
		if (!node->right)
			child = node->left;
		else
			child = heap->data_cmp(node->left->data, node->right->data) <= 0 ?
				node->left : node->right;
		if (heap->data_cmp(node->data, child->data) < 0)
			break;
		temp = node->data;
		node->data = child->data;
		child->data = temp;
		node = child;
	}
}

/**
 * heap_extract - extract the head heap_min
 * @heap: heap struct
 * Return: xtracted node's data
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *node;
	void *data;
	size_t bit;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL, heap->size--;
		return (data);
	}
	for (bit = 1; bit <= heap->size; bit <<= 1)
		;
	bit >>= 2;
	for (node = heap->root; bit > 0; bit >>= 1)
		node = heap->size & bit ? node->right : node->left;
	heap->root->data = node->data;
	if (node->parent->left == node)
		node->parent->left = NULL;
	else
		node->parent->right = NULL;
	heap->size--;
	free(node);
	heapify_down(heap);
	return (data);
}
