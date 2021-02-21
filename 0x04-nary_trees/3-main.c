#include <stdlib.h>
#include <stdio.h>

#include "nary_trees.h"

void print_node(nary_tree_t const *node, size_t depth)
{
	printf("%*s%s\n", (int)depth * 2, "", node->content);
}

int main(void)
{
	nary_tree_t *root, *tmp, *var, *opt, *betty, *home, *alex;
	size_t diameter;

	root = nary_tree_insert(NULL, "/");
	if (!root)
	{
		fprintf(stderr, "Failed to create node\n");
		return (EXIT_FAILURE);
	}

	tmp = nary_tree_insert(root, "tmp");
	nary_tree_insert(tmp, "tmp_file");

	var = nary_tree_insert(root, "var");
	nary_tree_insert(var, "www");

	opt = nary_tree_insert(root, "opt");
	betty = nary_tree_insert(opt, "Betty");
	nary_tree_insert(betty, "betty-style.pl");
	nary_tree_insert(betty, "betty-doc.pl");

	home = nary_tree_insert(root, "home");
	alex = nary_tree_insert(home, "alex");
	nary_tree_insert(alex, "Desktop");
	nary_tree_insert(alex, "Downloads");
	nary_tree_insert(alex, "Pictures");
	nary_tree_insert(alex, "Movies");
	nary_tree_insert(alex, "Documents");
	nary_tree_insert(alex, "Applications");

	diameter = nary_tree_diameter(root);
	printf("Diameter = %lu\n", diameter);

	nary_tree_delete(root);

	root = nary_tree_insert(NULL, "/");
	if (!root)
	{
		fprintf(stderr, "Failed to create node\n");
		return (EXIT_FAILURE);
	}

	tmp = nary_tree_insert(root, "tmp");

	nary_tree_insert(tmp, "tmp_file1");
	nary_tree_insert(tmp, "tmp_file2");

	home = nary_tree_insert(root, "home");

	alex = nary_tree_insert(home, "sthep");
	alex = nary_tree_insert(home, "danna");
	alex = nary_tree_insert(home, "alex");

	var = nary_tree_insert(alex, "Desktop");
	nary_tree_insert(alex, "Downloads");
	opt =nary_tree_insert(alex, "Pictures");

	home = nary_tree_insert(var, "Movies");

	nary_tree_insert(home, "Documents");
	var = nary_tree_insert(home, "Applications");

	home = nary_tree_insert(var, "Key");
	var = nary_tree_insert(home, "Value");


	betty = nary_tree_insert(opt, "Command");
	opt = nary_tree_insert(betty, "Cell");
	betty = nary_tree_insert(opt, "Mouse");

	diameter = nary_tree_diameter(root);
	printf("Diameter = %lu\n", diameter);

	nary_tree_traverse(root, &print_node);

	nary_tree_delete(root);

	return (EXIT_SUCCESS);
}
