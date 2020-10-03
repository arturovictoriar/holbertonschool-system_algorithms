#include "rb_trees.h"

void DeleteCase1(rb_tree_t *n);

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

void ReplaceNode(rb_tree_t *n, rb_tree_t *child)
{
	child->parent = n->parent;

	if (n == n->parent->left)
		n->parent->left = child;
	else
		n->parent->right = child;
}

void DeleteCase6(rb_tree_t *n)
{
	rb_tree_t *s = GETSIBLING(n);

	s->color = n->parent->color;
	n->parent->color = BLACK;

	if (n == n->parent->left)
	{
		s->right->color = BLACK;
		rotate(n->parent, 0);
	}
	else
	{
		s->left->color = BLACK;
		rotate(n->parent, 1);
	}
}

void DeleteCase5(rb_tree_t *n)
{
	rb_tree_t *s = GETSIBLING(n);

	if (s->color == BLACK)
	{
		if ((n == n->parent->left) && (s->right->color == BLACK) &&
			(s->left->color == RED))
		{
			s->color = RED, s->left->color = BLACK;
			rotate(s, 1);
		}
		else if ((n == n->parent->right) && (s->left->color == BLACK) &&
				 (s->right->color == RED))
		{
			s->color = RED, s->right->color = BLACK;
			rotate(s, 0);
		}
	}
	DeleteCase6(n);
}

void DeleteCase4(rb_tree_t *n)
{
	rb_tree_t *s = GETSIBLING(n);

	if ((n->parent->color == RED) && (s->color == BLACK) &&
		(s->left->color == BLACK) && (s->right->color == BLACK))
	{
		s->color = RED;
		n->parent->color = BLACK;
	}
	else
		DeleteCase5(n);
}

void DeleteCase3(rb_tree_t *n)
{
	rb_tree_t *s = GETSIBLING(n);

	if ((n->parent->color == BLACK) && (s->color == BLACK) &&
		(s->left->color == BLACK) && (s->right->color == BLACK))
	{
		s->color = RED;
		DeleteCase1(n->parent);
	}
	else
		DeleteCase4(n);
}

void DeleteCase2(rb_tree_t *n)
{
	rb_tree_t *s = GETSIBLING(n);

	if (s->color == RED)
	{
		n->parent->color = RED;
		s->color = BLACK;
		if (n == n->parent->left)
			rotate(n->parent, 0);
		else
			rotate(n->parent, 1);
	}
	DeleteCase3(n);
}

void DeleteCase1(rb_tree_t *n)
{
	if (n->parent != NULL)
		DeleteCase2(n);
}

void DeleteOneChild(rb_tree_t *n)
{
	rb_tree_t *child = (n->right == NULL) ? n->left : n->right;
	/* assert(child); */

	ReplaceNode(n, child);
	if (n->color == BLACK)
	{
		if (child->color == RED)
			child->color = BLACK;
		else
			DeleteCase1(child);
	}
	free(n);
}

rb_tree_t *two_child_nodes_change(rb_tree_t *node)
{
	rb_tree_t *min_val = node->right;

	/* loop down to find the leftmost leaf */
	while (min_val && min_val->left != NULL)
		min_val = min_val->left;

	node->n = min_val->n;
	return min_val;
}

rb_tree_t *search_value_in_tree(rb_tree_t *root, int n)
{
	rb_tree_t *node = NULL;

	if (!root)
		return NULL;

	if (n < root->n)
		node = search_value_in_tree(root->left, n);
	else if (n > root->n)
		node = search_value_in_tree(root->right, n);
	else
		return (root);

	return (node);
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
	new_root = WHATEVERNODE(node_found);

	if (!node_found->left && !node_found->right)
	{
		if (node_found->parent->left == node_found)
			node_found->parent->left = NULL;
		else
			node_found->parent->right = NULL;	
		free(node_found);
	}
	else if ((!node_found->left && node_found->right) ||
			 (node_found->left && !node_found->right))
		DeleteOneChild(node_found);
	else
	{
		node_found = two_child_nodes_change(node_found);
		new_root = WHATEVERNODE(node_found);
		if (!node_found->left && !node_found->right)
		{
			if (node_found->parent->left == node_found)
				node_found->parent->left = NULL;
			else
				node_found->parent->right = NULL;	
			free(node_found);
		}
		else if ((!node_found->left && node_found->right) ||
				 (node_found->left && !node_found->right))
			DeleteOneChild(node_found);
	}
	printf("%d \n", new_root->n);
	if (!new_root)
		return (NULL);
	while (GETPARENT(new_root))
		new_root = GETPARENT(new_root);
	return new_root;
}