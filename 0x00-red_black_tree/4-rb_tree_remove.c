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
 * rb_replace_node - select the succesor node who replace the delete node
 * @node: node to delete
 * Return: a pointer to the susccesor node, NULL otherwise
 */
rb_tree_t *rb_replace_node(rb_tree_t *node)
{
	rb_tree_t *temp = NULL;

	if (node->left && node->right)
	{
		temp = node->right;
		while (temp->left)
			temp = temp->left;
		return (temp);
	}

	if (!node->left && !node->right)
		return (NULL);

	if (node->left)
		return (node->left);
	else
		return (node->right);
}

/**
 * search_value_in_tree - check if a number is in the RB_tree
 * @root: root node of the RED-BLACK tree
 * @n: number to search
 * Return: the pointer to the node who contain n
 */
rb_tree_t *search_value_in_tree(rb_tree_t *root, int n)
{
	rb_tree_t *node = NULL;

	if (!root)
		return (NULL);

	if (n < root->n)
		node = search_value_in_tree(root->left, n);
	else if (n > root->n)
		node = search_value_in_tree(root->right, n);
	else
		return (root);

	return (node);
}

/**
 * sibling_is_red - fix RB_tree when the sibling is red
 * @sibling: deleted node's sibling
 * @parent: deleted node's parent
 * Return: nothing
 */
void sibling_is_red(rb_tree_t *sibling, rb_tree_t *parent)
{
	if (sibling->left && sibling->left->color == RED)
	{
		if (sibling->parent->left == sibling)
		{
			sibling->left->color = sibling->color;
			sibling->color = parent->color;
			rotate(parent, 1);
		}
		else
		{
			sibling->left->color = parent->color;
			rotate(sibling, 1);
			rotate(parent, 0);
		}
	}
	else
	{
		if (sibling->parent->left == sibling)
		{
			sibling->right->color = parent->color;
			rotate(sibling, 0);
			rotate(parent, 1);
		}
		else
		{
			sibling->right->color = sibling->color;
			sibling->color = parent->color;
			rotate(parent, 0);
		}
	}
	parent->color = BLACK;
}

/**
 * fix_double_black - fix the RB-tree after a node deletion of a node black
 * @node: node to fix the double black
 * Return: nothing
 */
void fix_double_black(rb_tree_t *node)
{
	rb_tree_t *sibling = GETSIBLING(node), *parent = node->parent;

	if (!GETPARENT(node))
		return;
	if (!sibling)
		fix_double_black(parent);
	else
	{
		if (sibling->color == RED)
		{
			parent->color = RED, sibling->color = BLACK;
			if (sibling->parent->left == sibling)
				rotate(parent, 1);
			else
				rotate(parent, 0);
			fix_double_black(node);
		}
		else
		{
			if (SIBLING_RED(sibling))
				sibling_is_red(sibling, parent);
			else
			{
				sibling->color = RED;
				if (parent->color == BLACK)
					fix_double_black(parent);
				else
					parent->color = BLACK;
			}
		}
	}
}

/**
 * rb_delete_node - delete a node of a RED-BLACK tree
 * @node: node to delete
 * Return: a pointer of the tree for letting search the new root, NULL otherw
 */
rb_tree_t *rb_delete_node(rb_tree_t *node)
{
	rb_tree_t *succesor = rb_replace_node(node), *parent = GETPARENT(node);
	int double_black = D_BLACK(node, succesor), temp = 0;

	if (!succesor)
	{
		if (parent)
		{
			if (double_black)
				fix_double_black(node);
			else if (GETSIBLING(node))
				GETSIBLING(node)->color = RED;
			if (parent->left == node)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		free(node);
		return (parent ? parent : NULL);
	} else if (!node->left || !node->right)
	{
		if (!GETPARENT(node))
		{
			node->n = succesor->n, node->left = node->right = NULL;
			free(succesor);
			return (node);
		}
		if (node->parent->left == node)
			parent->left = succesor;
		else
			parent->right = succesor;
		free(node);
		succesor->parent = parent;
		if (double_black)
			fix_double_black(succesor);
		else
			succesor->color = BLACK;
		return (succesor);
	}
	temp = node->n, node->n = succesor->n, succesor->n = temp;
	return (rb_delete_node(succesor));
}

/**
 * rb_tree_remove - remove a number from a RED-BLACK tree
 * @root: root node of the R-B tree
 * @n: value to remove in the R-B tree
 * Return: the new root node after deleting a node, NULL otherwise
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *node_found = NULL, *new_root = NULL;

	if (!root)
		return (root);
	node_found = search_value_in_tree(root, n);
	if (!node_found)
		return (root);

	new_root = rb_delete_node(node_found);

	if (!new_root)
		return (NULL);
	while (GETPARENT(new_root))
		new_root = GETPARENT(new_root);
	return (new_root);
}
