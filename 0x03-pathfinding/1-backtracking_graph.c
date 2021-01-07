#include "pathfinding.h"
#include <string.h>

/**
 * free_start_target_list_ver - free the copy of the start and target vertices
 * @s: start vertice
 * @t: target vertice
 * @list_ver: list of vertices
 * Return: Nothing
 */
void free_start_target_list_ver(vertex_t *s, vertex_t *t, char *list_ver)
{
	free(s);
	free(t);
	free(list_ver);
}

/**
 * make_path - build a queue representation of the path
 * @p: paht queue
 * @v: vertice to save in path
 * Return: 1 on success, 0 otherwise
 */
int make_path(queue_t *p, vertex_t *v)
{
	char *s = NULL;

	s = calloc(strlen(v->content) + 1, sizeof(char));
	strcpy(s, v->content);
	queue_push_front(p, (void *) s);

	return (1);
}

/**
 * find_path_recursive - find a path from start to target using backtracking
 * @l: vertices visited
 * @s: start vertice
 * @t: target vertice
 * @p: path queue
 * Return: 1 on success, 0 otherwise
 */
int find_path_recursive(char *l, vertex_t *s, vertex_t *t, queue_t *p)
{
	edge_t *e = NULL;
	vertex_t *v = NULL;

	printf("Checking %s\n", s->content);

	if (s->index == t->index)
		return (make_path(p, s));

	if (l[s->index] == '1')
		return (0);

	l[s->index] = '1';
	e = s->edges;
	while (e)
	{
		v = e->dest;
		if (l[v->index] == '0')
			if (find_path_recursive(l, v, t, p))
				return (make_path(p, s));
		e = e->next;
	}

	return (0);
}

/**
 * backtracking_graph - find a path from start to target using backtracking
 * @graph: representation of a complete graph vertices
 * @start: start point
 * @target: target point
 * Return: a queue path on success, NULL otherwise
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	queue_t *path = NULL;
	vertex_t *s = NULL, *t = NULL;
	char *list_ver = NULL;
	size_t i = 0;

	list_ver = calloc(graph->nb_vertices, sizeof(char));
	while (i < graph->nb_vertices)
	{
		list_ver[i] = '0';
		i++;
	}

	s = calloc(1, sizeof(vertex_t));
	t = calloc(1, sizeof(vertex_t));

	s->x = start->x, s->y = start->y, s->index = start->index;
	s->content = start->content, s->nb_edges = start->nb_edges;
	s->edges = start->edges, s->next = start->next;

	t->x = target->x, t->y = target->y, t->index = target->index;
	t->content = target->content, t->nb_edges = target->nb_edges;
	t->edges = target->edges, t->next = target->next;

	path = queue_create();
	if (!find_path_recursive(list_ver, s, t, path))
	{
		free_start_target_list_ver(s, t, list_ver);
		queue_delete(path);
		return (NULL);
	}

	free_start_target_list_ver(s, t, list_ver);

	return (path);
}
