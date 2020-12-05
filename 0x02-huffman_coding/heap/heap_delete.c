#include "heap.h"

/**
* delete_heap_recursive - delete all the nodes of a tree
* @root: pointert to the head of a tree
* @free_data: function pointer theat free data of a node
* Return: Nothing
*/
void delete_heap_recursive(binary_tree_node_t *root, void (*free_data)(void *))
{
	if (!root)
		return;

	delete_heap_recursive(root->left, free_data);
	delete_heap_recursive(root->right, free_data);
	if (free_data)
		free_data(root->data);
	free(root);
}

/**
 * heap_delete - delete a Min Binary Heap
 * @heap: pointer to the heap in which the node has to be inserted
 * @free_data:  pointer function that free data of a node
 * Return: Nothing
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	if (heap->root)
		delete_heap_recursive(heap->root, free_data);
	free(heap);
}
