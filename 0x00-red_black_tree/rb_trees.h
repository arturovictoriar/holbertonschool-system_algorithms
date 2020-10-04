#ifndef _RB_TREES_H_
#define _RB_TREES_H_

#include <stdio.h>
#include <stdlib.h>

#define GETPARENT(node) ((node == NULL) ? NULL : node->parent)
#define GETGRANDPARENT(node) GETPARENT(GETPARENT(node))
#define GETSIBLING(node) \
	(GETPARENT(node) ? \
	((node == (GETPARENT(node)->left)) ? \
	(GETPARENT(node)->right) : \
	(GETPARENT(node)->left)) : \
	NULL)
#define GETUNCLE(node) GETSIBLING(GETPARENT(node))
#define WHATEVERNODE(node_found) (\
	node_found->parent ? \
	node_found->parent : \
	(node_found->left ? \
	node_found->left : \
	(node_found->right ? \
	node_found->right : \
	NULL)))

/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 * @DOUBLE_BLACK: 2 -> Double-black node (used for deletion)
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
rb_tree_t *array_to_rb_tree(int *array, size_t size);
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);

#endif /* _RB_TREES_H_ */
