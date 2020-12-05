#include "heap.h"

/**
* binary_tree_node - create a node of a binary tree
* @parent: parent node
* @data: data to store in the node
* Return: a node of a binary tree, NULL otherwise
*/
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new_node = NULL;


	new_node = malloc(sizeof(binary_tree_node_t));
	if (!new_node)
		return (NULL);

	new_node->data = data;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
