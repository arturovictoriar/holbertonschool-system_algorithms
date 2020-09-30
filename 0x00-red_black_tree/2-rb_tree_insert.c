#include "rb_trees.h"

/**
 * rotate - rote a segment of a Btree
 * @node: node to rotate
 * @left_or_right: sense of the rotate (1 right, 0 left)
 * Return: nothing
 */
void rotate(rb_tree_t *node, int left_or_right)
{
	rb_tree_t *rot_new = NULL, *parent = GETPARENT(node);

	rot_new = left_or_right ? node->left : node->right;
	if (left_or_right)
	{
		node->left = rot_new->right;
		rot_new->right = node;
		node->parent = rot_new;

		/* Handle other child/parent pointers. */
		if (node->left)
			node->left->parent = node;
		/* Initially n could be the root. */
		if (parent)
		{
			if (node == parent->left)
				parent->left = rot_new;
			else if (node == parent->right)
				parent->right = rot_new;
		}
	}
	else
	{
		node->right = rot_new->left;
		rot_new->left = node;
		node->parent = rot_new;

		/* Handle other child/parent pointers. */
		if (node->right)
			node->right->parent = node;
		/* Initially n could be the root. */
		if (parent)
		{
			if (node == parent->left)
				parent->left = rot_new;
			else if (node == parent->right)
				parent->right = rot_new;
		}
	}
	rot_new->parent = parent;
}

/**
 * insert_value_recursive - insert a value in a RED_BLACK tree recursively
 * @root: root node of the RED-BLACK tree
 * @value: number to be insert
 * Return: A pointer with the node inserted, NULL otherwise
 */
rb_tree_t *insert_value_recursive(rb_tree_t *root, int value)
{
	rb_tree_t *new_node = NULL;

	if (root)
	{
		if (value < root->n)
		{
			if (root->left)
				return (insert_value_recursive(root->left, value));

			new_node = rb_tree_node(root, value, RED);
			if (!new_node)
				return (NULL);
			root->left = new_node;
		}
		else if (value > root->n)
		{
			if (root->right)
				return (insert_value_recursive(root->right, value));

			new_node = rb_tree_node(root, value, RED);
			if (!new_node)
				return (NULL);
			root->right = new_node;
		}
		else
			return (NULL);
	}
	return (new_node);
}

/**
 * repair_rb_tree - make back a RB Tree
 * @node: node where starting the fixing
 * Return: Nothing
 */
void repair_rb_tree(rb_tree_t *node)
{
	rb_tree_t *parent = NULL, *grand_pa = NULL;

	if (!GETPARENT(node))
		node->color = BLACK;
	else if (GETPARENT(node)->color == BLACK)
		return;
	else if (GETUNCLE(node) && (GETUNCLE(node))->color == RED)
	{
		GETPARENT(node)->color = BLACK, GETUNCLE(node)->color = BLACK;
		GETGRANDPARENT(node)->color = RED;
		repair_rb_tree(GETGRANDPARENT(node));
	}
	else
	{
		parent = GETPARENT(node);
		grand_pa = GETGRANDPARENT(node);

		if (node == parent->right && parent == grand_pa->left)
		{
			rotate(parent, 0);
			node = node->left;
		}
		else if (node == parent->left && parent == grand_pa->right)
		{
			rotate(parent, 1);
			node = node->right;
		}

		parent = GETPARENT(node);
		grand_pa = GETGRANDPARENT(node);

		if (node == parent->left)
			rotate(grand_pa, 1);
		else
			rotate(grand_pa, 0);
		parent->color = BLACK, grand_pa->color = RED;
	}
}

/**
 * rb_tree_insert - insert a given value in a Red_black tree
 * @tree: root of the binary tree
 * @value: number to insert in the Red_black tree
 * Return: The pointer of the new node inserted on success, NULL otherwise
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node = NULL, *new_root = NULL;

	if (!*tree)
		return (*tree = rb_tree_node(NULL, value, BLACK));

	new_node = insert_value_recursive(*tree, value);
	if (!new_node)
		return (NULL);

	repair_rb_tree(new_node);

	new_root = new_node;
	while (GETPARENT(new_root) != NULL)
		new_root = GETPARENT(new_root);
	*tree = new_root;

	return (new_node);
}
