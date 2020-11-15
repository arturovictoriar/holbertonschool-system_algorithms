#include "graphs.h"

/**
 * create_vertex - create a new vertix
 * @graph: the graph struct
 * @str: string to store as content of the vertix
 * Return: a vertix pointer on succes or NULL otherwise
 */
vertex_t *create_vertex(graph_t *graph, const char *str)
{
	unsigned int len_s = 0;
	char *cp_str = NULL;
	vertex_t *new_v = NULL;

	new_v = malloc(sizeof(vertex_t));
	if (!new_v)
		return (NULL);

	len_s = strlen(str);
	cp_str = malloc(sizeof(char) * (len_s + 1));
	if (!cp_str)
	{
		free(new_v);
		return (NULL);
	}

	new_v->content = strcpy(cp_str, str);
	new_v->index = graph->nb_vertices;
	new_v->nb_edges = 0;
	new_v->edges = NULL;
	new_v->next = NULL;

	return (new_v);
}

/**
 * graph_add_vertex - add a vertix to a graph
 * @graph: the graph struct
 * @str: string to store as content of the vertix
 * Return: a vertix pointer on succes or NULL otherwise
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *cp_ver_head = NULL, *new_v = NULL;

	if (!graph || !str)
		return (NULL);

	cp_ver_head = graph->vertices;

	while (cp_ver_head)
	{
		if (!strcmp(str, cp_ver_head->content))
			return (NULL);
		if (cp_ver_head->next)
			cp_ver_head = cp_ver_head->next;
		else
			break;
	}

	new_v = create_vertex(graph, str);
	if (!new_v)
		return (NULL);

	if (cp_ver_head)
		cp_ver_head->next = new_v;
	else
		graph->vertices = new_v;

	graph->nb_vertices++;
	return (new_v);
}
