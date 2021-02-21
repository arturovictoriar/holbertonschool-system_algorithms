#include "nary_trees.h"

/**
* nary_tree_delete - deallocate a entire nary tree
* @tree: head of a nary tree
* Return: nothing
*/
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *next_node = NULL, *children = NULL;

	if (tree == NULL)
		return;

	children = tree->children;
	while (children)
	{
		nary_tree_delete(children->children);
		free(children->content);
		next_node = children->next;
		free(children);
		children = next_node;
	}
	free(tree->content);
	free(tree);
}
