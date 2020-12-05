#include "heap.h"

/**
 * fix_min_heap - fix the tree to achieve a min heap tree
 * @new_node: node inserted in the min heap tree
 * @heap: heap structure
 * Return: 1 on succes
 */
int fix_min_heap(binary_tree_node_t *new_node, heap_t *heap)
{
	binary_tree_node_t *temp_parent = NULL;
	binary_tree_node_t *temp_l = NULL, *temp_r = NULL, *temp_g = NULL;

	while (new_node->parent &&
			heap->data_cmp(new_node->data, new_node->parent->data) < 0)
	{
		temp_parent = new_node->parent, temp_g = temp_parent->parent;
		temp_l = new_node->left, temp_r = new_node->right;
		if (temp_parent->left == new_node)
		{
			new_node->left = temp_parent, new_node->right = temp_parent->right;
			if (temp_parent->right)
				temp_parent->right->parent = new_node;
		}
		else
		{
			new_node->right = temp_parent, new_node->left = temp_parent->left;
			if (temp_parent->left)
				temp_parent->left->parent = new_node;
		}
		new_node->parent = temp_g;
		if (temp_g && temp_g->left == temp_parent)
			temp_g->left = new_node;
		else if (temp_g && temp_g->right == temp_parent)
			temp_g->right = new_node;
		temp_parent->parent = new_node;
		if (temp_l)
			temp_l->parent = temp_parent;
		if (temp_r)
			temp_r->parent = temp_parent;
		temp_parent->left = temp_l, temp_parent->right = temp_r;
	}

	return (1);
}

/**
 * insert_node_at_end - insert a given node in the button of the tree
 * @root: head of tree
 * @node: node to insert
 * @deep: current deep
 * @d_target: deep to reach
 * Return: 1 on success, 0 otherwise
 */
int insert_node_at_end(binary_tree_node_t *root, binary_tree_node_t *node,
		long deep, long d_target)
{
	int l = 0, r = 0;

	if (deep == d_target)
	{
		if (!root->left)
			root->left = node, node->parent = root;
		else if (!root->right)
			root->right = node, node->parent = root;
		else
			return (0);
		return (1);
	}

	l = insert_node_at_end(root->left, node, deep + 1, d_target);
	if (l)
		return (l);
	r = insert_node_at_end(root->right, node, deep + 1, d_target);
	if (r)
		return (r);

	return (0);
}

/**
 * get_deep - getting the deep of the tree
 * @size: number of nodes in the tree
 * Return: the deep of the tree
 */
long get_deep(long size)
{
	long num_nodes = 1, deep = 0;

	while (size >= num_nodes)
		num_nodes += (1 << (deep + 1)), deep++;

	return (deep);
}

/**
 * heap_insert - inserts a value in a Min Binary Heap
 * @heap: pointer to the heap in which the node has to be inserted
 * @data:  pointer containing the data to store in the new node
 * Return: a pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node = NULL;
	int node_inserted = 0;

	if (!heap)
		return (NULL);
	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);
	if (!heap->root)
		return (heap->size++, heap->root = new_node, new_node);
	node_inserted = insert_node_at_end(heap->root, new_node,
			0, get_deep(heap->size) - 1);
	if (!node_inserted)
		return (free(new_node), NULL);

	fix_min_heap(new_node, heap);

	if (!new_node->parent)
		heap->root = new_node;
	return (heap->size++, new_node);
}
