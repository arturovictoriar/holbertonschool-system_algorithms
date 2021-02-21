#include "nary_trees.h"

#define MAX(a, b) ((a > b) ? a : b)

/**
 * nary_d - test all posibles diameters and get the maximun
 * @r: root of the nary tree
 * @dia: variable to store the max diameter in the nary tree
 * Return: the depth + 1 of the nary tree
 */
int nary_d(nary_tree_t *r, int *dia)
{
	int m1 = 0, m2 = 0, cd = 0, d = 0;
	nary_tree_t *children = NULL;

	if (r == NULL)
		return (-1);

	children = r->children;
	while (children)
	{
		d = nary_d(children, dia);
		cd = MAX(cd, d);
		if (d > m1)
		{
			m2 = m1;
			m1 = d;
		}
		else if (d > m2)
		{
			m2 = d;
		}
		children = children->next;
	}

	*dia = MAX((m1 + m2 + 1), *dia);
	return (cd + 1);
}

/**
 * nary_tree_diameter - get the diameter of an nary
 * @root: root of the nary tree
 * Return: the diameter of the nary tree
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	int dia = 0;

	if (root == NULL)
		return (0);

	nary_d((nary_tree_t *) root, &dia);
	return (dia);
}
