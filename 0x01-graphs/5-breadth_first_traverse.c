#include "graphs.h"

/**
 * recur_traverse - breadth first traverse with recursive, look for all nodes
 * @cp_ve_header: vertix header
 * @len_gra: lenght of the graph
 * @depth: current detph
 * @m_depth: max detph of traverse
 * @action: function pointer which print an the current value node
 * Return: the deepest depth on success or 0 otherwise
 */
size_t recur_traverse(vertex_t *cp_ve_header, char *len_gra, size_t depth,
					  size_t m_depth, void (*action)(const vertex_t *v, size_t depth))
{
	size_t flag = 0;
	edge_t *cp_ed_header = NULL;

	if (!cp_ve_header)
		return (0);
	cp_ed_header = cp_ve_header->edges;
	if (depth != m_depth)
		return (recur_traverse(cp_ed_header->dest,
							   len_gra, depth + 1, m_depth, action));

	while (cp_ed_header)
	{
		if (len_gra[cp_ed_header->dest->index] == 0)
		{
			action(cp_ed_header->dest, depth);
			len_gra[cp_ed_header->dest->index] = 1;
			flag = 1;
		}
		cp_ed_header = cp_ed_header->next;
	}
	if (!flag)
		return (0);
	return (depth);
}

/**
 * iter_traverse - breadth first traverse with iteration, iterate each edge
 * @cp_ve_header: vertix header
 * @len_gra: lenght of the graph
 * @action: function pointer which print an the current value node
 * Return: the deepest depth on success or 0 otherwise
 */
size_t iter_traverse(vertex_t *cp_ve_header, char *len_gra,
					 void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth_n = 0, max_depth = 0, flag = 0, flag_e = 1, i = 2;
	edge_t *cp_ed_header = NULL;

	cp_ed_header = cp_ve_header->edges;
	while (cp_ed_header)
	{
		if (len_gra[cp_ed_header->dest->index] == 0)
		{
			action(cp_ed_header->dest, 1);
			len_gra[cp_ed_header->dest->index] = 1;
			flag = 1;
		}
		cp_ed_header = cp_ed_header->next;
	}
	if (flag)
		max_depth = 1;
	while (flag_e != 0)
	{
		flag_e = 0;
		cp_ed_header = cp_ve_header->edges;
		while (cp_ed_header)
		{
			depth_n = recur_traverse(cp_ed_header->dest, len_gra, 2, i, action);
			if (depth_n > max_depth)
				max_depth = depth_n;
			if (depth_n > 0)
				flag_e = 1;
			cp_ed_header = cp_ed_header->next;
		}
		i++;
	}
	return (max_depth);
}

/**
 * breadth_first_traverse - run through a graph using breadth first traverse
 * @graph: the graph struct
 * @action: function pointer which print an the current value node
 * Return: the deepest depth on success or 0 otherwise
 */
size_t breadth_first_traverse(const graph_t *graph,
							  void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t *cp_ve_header = NULL;
	char len_gra[2048] = {0};
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
			depth_n = iter_traverse(cp_ve_header, len_gra, action);
			if (depth_n > max_depth)
				max_depth = depth_n;
		}
		cp_ve_header = cp_ve_header->next;
		break;
	}
	return (max_depth);
}
