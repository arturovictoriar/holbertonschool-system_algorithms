#include "heap.h"

/**
* swap_nodes - swap 2 given numbers
* @node1: heap node to swap
* @node2: heap node to swap
* Return: nothing
*/
void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	binary_tree_node_t *temp_parent = NULL;
	binary_tree_node_t *temp_l = NULL, *temp_r = NULL, *temp_g = NULL;

	temp_parent = node1, temp_g = temp_parent->parent;
	temp_l = node2->left, temp_r = node2->right;
	if (temp_parent->left == node2)
	{
		node2->left = temp_parent, node2->right = temp_parent->right;
		if (temp_parent->right)
			temp_parent->right->parent = node2;
	}
	else
	{
		node2->right = temp_parent, node2->left = temp_parent->left;
		if (temp_parent->left)
			temp_parent->left->parent = node2;
	}
	node2->parent = temp_g;
	if (temp_g && temp_g->left == temp_parent)
		temp_g->left = node2;
	else if (temp_g && temp_g->right == temp_parent)
		temp_g->right = node2;
	temp_parent->parent = node2;
	if (temp_l)
		temp_l->parent = temp_parent;
	if (temp_r)
		temp_r->parent = temp_parent;
	temp_parent->left = temp_l, temp_parent->right = temp_r;
}

/**
 * fix_min_heap_e - fix the tree to achieve a min heap tree
 * @root: node inserted in the min heap tree
 * @heap: heap structure
 * Return: 1 on succes
 */
binary_tree_node_t *fix_min_heap_e(binary_tree_node_t *root, heap_t *heap)
{
	binary_tree_node_t *new_root = root;
	int flag = 1;

	while ((root->left && heap->data_cmp(root->data, root->left->data) > 0) ||
			(root->right && heap->data_cmp(root->data, root->right->data) > 0))
	{
		if (root->left && root->right)
		{
			if (heap->data_cmp(root->data, root->left->data) >=
					heap->data_cmp(root->data, root->right->data))
				swap_nodes(root, root->left);
			else
				swap_nodes(root, root->right);
		}
		else if (root->left && !root->right)
			swap_nodes(root, root->left);
		if (flag == 1)
			flag = 0, new_root = root->parent;
	}

	return (new_root);
}

/**
 * get_last_node - get the last node of a min heap
 * @root: head of tree
 * @deep: current deep
 * @d_target: deep to reach
 * Return: pointer to the last node or NULL otherwise
 */
binary_tree_node_t *get_last_node(binary_tree_node_t *root,
		long deep, long d_target)
{
	binary_tree_node_t *l = NULL, *r = NULL;

	if (!root)
		return (NULL);

	if (deep == d_target)
	{
		if (root->left && !root->right)
			return (root->left);
		else if (root->left && root->right)
			return (root->right);
		else
			return (NULL);
	}

	l = get_last_node(root->left, deep + 1, d_target);
	r = get_last_node(root->right, deep + 1, d_target);

	if (l && !r)
		return (l);
	else if (l && r)
		return (r);
	return (NULL);
}

/**
 * get_deep_e - getting the deep of the tree
 * @size: number of nodes in the tree
 * Return: the deep of the tree
 */
long get_deep_e(long size)
{
	long num_nodes = 1, deep = 0;

	while (size > num_nodes)
		num_nodes += (1 << (deep + 1)), deep++;

	return (deep);
}

/**
 * heap_extract - extract a node from a Min Binary Heap
 * @heap: pointer to the heap in which the node has to be inserted
 * Return: Nothing
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last_node = NULL, *root = NULL;
	void *data = NULL;
	long deep = 0;

	if (!heap || !heap->root)
		return (NULL);
	deep = get_deep_e(heap->size) - 1;
	last_node = get_last_node(heap->root, 0, deep);
	if (!last_node)
	{
		root = heap->root;
		heap->root = NULL;
		data = root->data;
		free(root);
		heap->size--;
		return (data);
	}
	root = heap->root;
	if (last_node->parent->left == last_node)
		last_node->parent->left = NULL;
	else
		last_node->parent->right = NULL;
	last_node->parent = NULL;
	if (root->left)
		root->left->parent = last_node;
	if (root->right)
		root->right->parent = last_node;
	last_node->left = root->left;
	last_node->right = root->right;

	heap->root = last_node;
	data = root->data;
	free(root);
	heap->size--;

	heap->root = fix_min_heap_e(heap->root, heap);

	return (data);
}
