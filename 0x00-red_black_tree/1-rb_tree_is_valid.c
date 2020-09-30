#include "rb_trees.h"

/**
* is_BTS_and_colors - verify is the tree is BTS, if each node has a color
* , if there is not exist 2 consecutive red nodes, and if all path has the
* same nums of black nodes
* @tree: root of the tree
* @prev_color: previous node color
* @num_black: number of black nodes of the tree
* @num_black_path: number of black nodes that each path has
* Return: 1 on success, 0 otherwise
*/
int is_BTS_and_colors(rb_tree_t *tree, int prev_color, int num_black,
	int num_black_path)
{
	int left = 0, right = 0;

	if (!tree)
	{
		if (num_black == num_black_path + 1)
			return (1);
		return (0);
	}

	if ((tree->color != BLACK && tree->color != RED) ||
		(prev_color == 1 && tree->color == RED))
		return (0);

	if ((tree->left != NULL && tree->n < tree->left->n) ||
		(tree->right != NULL && tree->n > tree->right->n))
		return (0);

	if (tree->color == BLACK)
	{
		left = is_BTS_and_colors(tree->left, (tree->color == RED) ? 1 : 0,
			num_black, num_black_path + 1);
		if (!left)
			return (0);
		right = is_BTS_and_colors(tree->right, (tree->color == RED) ? 1 : 0,
			num_black, num_black_path + 1);
		if (!right)
			return (0);
	}
	else
	{
		left = is_BTS_and_colors(tree->left, (tree->color == RED) ? 1 : 0,
			num_black, num_black_path);
		if (!left)
			return (0);
		right = is_BTS_and_colors(tree->right, (tree->color == RED) ? 1 : 0,
			num_black, num_black_path);
		if (!right)
			return (0);
	}
	return (1);
}

/**
* rb_tree_is_valid - verify if a given tree is a red-black tree
* @tree: root node of the tree
* Return: 1 on success, 0 otherwise
*/
int rb_tree_is_valid(const rb_tree_t *tree)
{
	rb_tree_t *tree_copy = (rb_tree_t *) tree;
	int num_black = 0;

	if (!tree || tree->color == RED)
		return (0);

	while (tree_copy)
	{
		if (tree_copy->color == BLACK)
			num_black++;
		tree_copy = tree_copy->left;
		if (!tree_copy)
			num_black++;
	}
	if (!is_BTS_and_colors((rb_tree_t *) tree, 2, num_black, 0))
		return (0);
	return (1);
}
