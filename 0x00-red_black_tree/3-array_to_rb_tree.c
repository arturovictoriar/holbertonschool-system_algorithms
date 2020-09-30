#include "rb_trees.h"

/**
 * array_to_rb_tree - convert an array to a RED_BLACK tree
 * @array: list of number to convert
 * @size: size of the list
 * Return: the root of the tree
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	unsigned int index1 = 0, index2 = 0, jump = 0;
	rb_tree_t *root = NULL;

	for (index1 = 0; index1 < size; index1++)
	{
		for (index2 = 0; index2 < index1; index2++)
		{
			if (array[index1] == array[index2])
			{
				jump = 1;
				break;
			}
		}

		if (jump)
			jump = 0;
		else if (!rb_tree_insert(&root, array[index1]))
			return (NULL);
	}

	return (root);
}
