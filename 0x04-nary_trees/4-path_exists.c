#include "nary_trees.h"

/**
* exists_path - chechk if a given path exist in a nary tree
* @root: root of a nary tree
* @path: NULL terminated list of string reprensent of a path
* Return: 1 if the path exists, 0 otherwise
*/
int exists_path(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t const *n = NULL;

	if (*path == NULL)
		return (1);
	if (root == NULL)
		return (0);

	n = root;
	while (n)
	{
		if (strcmp(*path, n->content) == 0)
			if (exists_path(n->children, path + 1) == 1)
				return (1);
		n = n->next;
	}

	return (0);
}

/**
* path_exists - chechk if a given path exist in a nary tree
* @root: root of a nary tree
* @path: NULL terminated list of string reprensent of a path
* Return: 1 if the path exists, 0 otherwise
*/
int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (root == NULL || path == NULL)
		return (0);
	return (exists_path(root, path));
}
