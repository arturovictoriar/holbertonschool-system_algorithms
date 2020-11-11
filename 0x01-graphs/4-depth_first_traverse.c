#include "graphs.h"

/**
 * recur_traverse - depth first traverse with recursion
 * @cp_ve_header: vertix header
 * @len_gra: lenght of the graph
 * @depth: detph of the first traverse
 * @action: function pointer which print an the current value node
 * Return: the deepest depth on success or 0 otherwise
 */
size_t recur_traverse(vertex_t *cp_ve_header, char *len_gra, size_t depth,
	void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth_n = 0, max_depth = depth, flag = 0;
	edge_t *cp_ed_header = NULL;

	if (!cp_ve_header)
		return (depth - 1);

	cp_ed_header = cp_ve_header->edges;
	while (cp_ed_header)
	{
		if (len_gra[cp_ed_header->dest->index] == 0)
		{
			action(cp_ed_header->dest, depth);
			len_gra[cp_ed_header->dest->index] = 1;
			depth_n = recur_traverse(cp_ed_header->dest, len_gra, depth + 1, action);
			if (depth_n > max_depth)
				max_depth = depth_n;
			flag = 1;
		}
		cp_ed_header = cp_ed_header->next;
	}
	if (flag)
		return (max_depth);
	return (max_depth - 1);
}

/**
 * depth_first_traverse - run through a graph using depth first traverse
 * @graph: the graph struct
 * @action: function pointer which print an the current value node
 * Return: the deepest depth on success or 0 otherwise
 */
size_t depth_first_traverse(const graph_t *graph,
							void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t *cp_ve_header = NULL;
	char len_gra[1024] = {0};
	size_t depth_n = 0, max_depth = 0;

	if (!graph)
		return (0);

	cp_ve_header = graph->vertices;

	while (cp_ve_header)
	{
		if (len_gra[cp_ve_header->index] == 0)
		{
			action(cp_ve_header, 0);
			len_gra[cp_ve_header->index] = 1;
			depth_n = recur_traverse(cp_ve_header, len_gra, 1, action);
			if (depth_n > max_depth)
				max_depth = depth_n;
		}
		cp_ve_header = cp_ve_header->next;
	}
	return (max_depth);
}
