#include "huffman.h"

/**
 * huffman_extract_and_insert - extract 2 min nodes and insert 1
 * @priority_queue: head ot heap tree
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1 = NULL, *node2 = NULL, *new_node = NULL;
	binary_tree_node_t *node_inserted = NULL;
	symbol_t *new_symbol = NULL;
	size_t new_freq = 0;

	if (!priority_queue || !priority_queue->root)
		return (0);

	node1 = (binary_tree_node_t *) heap_extract(priority_queue);
	if (!node1)
		return (0);
	node2 = (binary_tree_node_t *) heap_extract(priority_queue);
	if (!node2)
		return (0);
	new_freq = ((symbol_t *)node1->data)->freq + ((symbol_t *)node2->data)->freq;
	new_symbol = symbol_create(-1, new_freq);
	if (!new_symbol)
		return (0);

	new_node = binary_tree_node(NULL, new_symbol);
	if (!new_node)
		return (0);

	new_node->left = node1;
	node1->parent = new_node;
	new_node->right = node2;
	node2->parent = new_node;

	node_inserted = heap_insert(priority_queue, (void *) new_node);
	if (!node_inserted)
		return (0);

	return (1);
}
