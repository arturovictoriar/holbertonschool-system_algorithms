#include "graphs.h"

/**
 * create_edge - create an edge struct
 * @dest_v: the dest end point of the edge
 * Return: 1 on success, or 0 on failure
 */
edge_t *create_edge(vertex_t *dest_v)
{
	edge_t *new_e = NULL;

	new_e = malloc(sizeof(edge_t));
	if (!new_e)
		return (NULL);

	new_e->dest = dest_v;
	new_e->next = NULL;

	return (new_e);
}

/**
 * add_edge_linked_list - add an egde in the edge array vertix
 * @src_v: is a pointer to the vertix to add the edge to
 * @new_e1: the edge to add
 * Return: 1 on success, or 0 on failure
 */
int add_edge_linked_list(vertex_t *src_v, edge_t *new_e1)
{
	edge_t *cp_ed_head = NULL;

	if (!src_v->edges)
		src_v->edges = new_e1, src_v->nb_edges++;
	else
	{
		cp_ed_head = src_v->edges;
		while (cp_ed_head)
		{
			if (!cp_ed_head->next)
				break;
			cp_ed_head = cp_ed_head->next;
		}
		cp_ed_head->next = new_e1, src_v->nb_edges++;
	}

	return (1);
}

/**
 * graph_add_edge - add an egde in vertix
 * @graph: is a pointer to the graph to add the edge to
 * @src: is the string identifying the vertex to make the connection from
 * @dest: is the string identifying the vertex to connect to
 * @type: is the type of edge could be UNIDIRECTIONAL or BIDIRECTIONAL
 * Return: 1 on success, or 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
				   edge_type_t type)
{
	vertex_t *cp_ver_head = NULL, *src_v = NULL, *dest_v = NULL;
	edge_t *new_e1 = NULL, *new_e2 = NULL;

	if (!graph || !src || !dest || !strcmp(src, dest) ||
		(type != BIDIRECTIONAL && type != UNIDIRECTIONAL))
		return (0);
	cp_ver_head = graph->vertices;
	while (cp_ver_head)
	{
		if (!strcmp(cp_ver_head->content, src))
			src_v = cp_ver_head;
		else if (!strcmp(cp_ver_head->content, dest))
			dest_v = cp_ver_head;
		if (src_v && dest_v)
			break;
		cp_ver_head = cp_ver_head->next;
	}
	if ((!src_v && !dest_v) || (!src_v && dest_v) || (src_v && !dest_v))
		return (0);

	new_e1 = create_edge(dest_v);
	if (!new_e1)
		return (0);
	if (type == BIDIRECTIONAL)
	{
		new_e2 = create_edge(src_v);
		if (!new_e2)
		{
			free(new_e1);
			return (0);
		}
	}

	add_edge_linked_list(src_v, new_e1);
	if (type == BIDIRECTIONAL)
		add_edge_linked_list(dest_v, new_e2);

	return (1);
}
