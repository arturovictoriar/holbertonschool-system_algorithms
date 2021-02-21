#include "nary_trees.h"

/**
* create_nary_node - allocate memory for a new nary node
* Return: a new nary node on success, NULL otherwise
*/
nary_tree_t *create_nary_node(void)
{
	nary_tree_t *new_node = NULL;

	new_node = malloc(sizeof(nary_tree_t));
	if (new_node == NULL)
		return (NULL);

	new_node->content = NULL;
	new_node->parent = NULL;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;

	return (new_node);
}

/**
* nary_tree_insert - insert a new nary node in a given parent
* @parent: pointer to the parent of the new nary node
* @str: content to store in the new nary node
* Return: a new nary node on success, NULL otherwise
*/
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node = NULL;

	new_node = create_nary_node();
	if (new_node == NULL)
		return (NULL);

	new_node->content = strdup(str);
	if (parent == NULL)
		return (new_node);

	new_node->parent = parent;
	new_node->next = parent->children;

	parent->children = new_node;
	parent->nb_children++;

	return (new_node);
}
