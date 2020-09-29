#include "rb_trees.h"

/**
* rb_tree_node - create a node of a red-black tree
* @parent: parent node
* @value: value of the new node
* @color: color of the new node
* Return: a pointer to the new node on success, NULL otherwise
*/
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node = NULL;

	new_node = malloc(sizeof(rb_tree_t));
	if (!new_node)
		return (NULL);

	new_node->parent = parent;
	new_node->n = value;
	new_node->color = color;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
