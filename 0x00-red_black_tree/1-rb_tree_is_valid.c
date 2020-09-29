#include "rb_trees.h"

/**
* is_BTS_and_colors - verify is the tree is BTS, if each node has a color
* and if there is not exist 2 consecutive red nodes
* @tree: root of the tree
* @prev_color: previous node color
* Return: 1 on success, 0 otherwise
*/
int is_BTS_and_colors(rb_tree_t *tree, int prev_color)
{
	int left = 0, right = 0;

	if (!tree)
		return (1);

	if ((tree->color != BLACK && tree->color != RED) ||
		(prev_color == 1 && tree->color == RED))
		return (0);

	if ((tree->left != NULL && tree->n < tree->left->n) ||
		(tree->right != NULL && tree->n > tree->right->n))
		return (0);

	left = is_BTS_and_colors(tree->left, (tree->color == RED) ? 1 : 0);
	if (!left)
		return (0);

	right = is_BTS_and_colors(tree->right, (tree->color == RED) ? 1 : 0);
	if (!right)
		return (0);

	return (1);
}

/**
* same_black_node - verify if all path in tree has the same black nodes
* @tree: root node of the tree
* @num_black: number of black nodes of the tree
* @num_black_path: number of black nodes that each path has
* Return: 1 on success, 0 otherwise
*/
int same_black_node(rb_tree_t *tree, int num_black, int num_black_path)
{
	int same_black = 0;

	if (!tree)
	{
		if (num_black == num_black_path + 1)
			return (1);
		return (0);
	}

	if (tree->color == BLACK)
	{
		same_black = same_black_node(tree->left, num_black, num_black_path + 1);
		if (!same_black)
			return (0);
		same_black = same_black_node(tree->right, num_black, num_black_path + 1);
		if (!same_black)
			return (0);
	}
	else
	{
		same_black = same_black_node(tree->left, num_black, num_black_path);
		if (!same_black)
			return (0);
		same_black = same_black_node(tree->right, num_black, num_black_path);
		if (!same_black)
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

	if (!is_BTS_and_colors((rb_tree_t *) tree, 2))
		return (0);

	while (tree_copy)
	{
		if (tree_copy->color == BLACK)
			num_black++;
		tree_copy = tree_copy->left;
		if (!tree_copy)
			num_black++;
	}
	if (!same_black_node((rb_tree_t *) tree, num_black, 0))
		return (0);
	return (1);
}
