#include "pathfinding.h"
#include <string.h>

/**
 * free_list_unvisited_visited - free all the memory allocated
 * @list_ver: list of visited vertices
 * @unvisited: queue of unvisited vertices
 * @visited: queue of visited vertices
 * @path: queue of path from start to target
 * Return: Nothing
 */
void free_list_unvisited_visited(char *list_ver, queue_t *unvisited,
		queue_t *visited, queue_t *path)
{
	free(list_ver);
	queue_delete(unvisited);
	queue_delete(visited);
	if (!path->front)
		queue_delete(path);
}

/**
 * make_path - build a queue representation of the path
 * @p: paht queue
 * @v: vertice with the information to save in path
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
 * find_node_queue - find a vertices in a queue
 * @unvisited: Pointer queue with store all the vertices not visited
 * @neighbor: Pointer edge wich store the vertice wished
 * Return: A pointer node queue with the verticed found in unvisited
 */
queue_node_t *find_node_queue(queue_t *unvisited, edge_t *neighbor)
{
	queue_node_t *front = NULL;

	front = unvisited->front;
	while (front)
	{
		if (((vertex_t *) front->ptr)->index == neighbor->dest->index)
			break;
		front = front->next;
	}

	return (front);
}

/**
* dijkstra_algo - dijkstra algoritm applied on graph
* @start: start vertice
* @target: target vertice
* @visited: queue of visited vertices
* @unvisited: queue of unvisited vertices
* @list_ver: list of vertices visited
* Return: a vertex pointer with the target vertice
*/
vertex_t *dijkstra_algo(vertex_t *start, vertex_t *target, queue_t *visited,
		queue_t *unvisited, char *list_ver)
{
	vertex_t *visiting = start;
	edge_t *neighbors = NULL;
	queue_node_t *node_q = NULL;
	int x = 0;
	void *c_ptr = NULL;

	for (visiting->y = 0; visiting;)
	{
		printf("Checking %s, distance from %s is %d\n", visiting->content,
				start->content, visiting->y);
		if (visiting->index == target->index)
			break;
		list_ver[visiting->index] = '1', neighbors = visiting->edges;
		for (node_q = NULL; neighbors; node_q = NULL, neighbors = neighbors->next)
		{
			if ((list_ver[neighbors->dest->index] == '0') &&
					((neighbors->dest->y > (visiting->y + neighbors->weight)) ||
					 (neighbors->dest->y == -1)))
			{
				x = neighbors->dest->x;
				neighbors->dest->x = visiting->index;
				neighbors->dest->y = visiting->y + neighbors->weight;
				if (x == -1)
					node_q = queue_push_back(unvisited, (void *) neighbors->dest);
				else
					node_q = find_node_queue(unvisited, neighbors);
			}
			while (node_q && node_q->prev &&
					((vertex_t *) node_q->prev->ptr)->y > ((vertex_t *) node_q->ptr)->y)
			{
				c_ptr = node_q->prev->ptr;
				node_q->prev->ptr = node_q->ptr;
				node_q->ptr = c_ptr;
				node_q = node_q->prev;
			}
		}
		queue_push_front(visited, (void *) visiting);
		visiting = (vertex_t *) dequeue(unvisited);
	}
	return (visiting);
}

/**
 * dijkstra_graph - find a path from start to target using dijkstra in graph
 * @graph: representation of a complete graph vertices
 * @start: start point
 * @target: target point
 * Return: a queue path on success, NULL otherwise
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	queue_t *path = NULL, *unvisited = NULL, *visited = NULL;
	queue_node_t *front_q = NULL;
	vertex_t *visiting = NULL, *all_vertices = NULL;
	char *list_ver = NULL;
	size_t i = 0;
	int x = 0;

	list_ver = calloc(graph->nb_vertices, sizeof(char));
	for (i = 0; i < graph->nb_vertices; i++)
		list_ver[i] = '0';

	all_vertices = graph->vertices;
	for (; all_vertices; all_vertices = all_vertices->next)
		all_vertices->x = -1, all_vertices->y = -1;

	path = queue_create();
	unvisited = queue_create();
	visited = queue_create();

	visiting = dijkstra_algo((vertex_t *) start, (vertex_t *) target, visited,
			unvisited, list_ver);
	if (!visiting)
	{
		free_list_unvisited_visited(list_ver, unvisited, visited, path);
		return (NULL);
	}

	make_path(path, visiting);
	x = visiting->x;
	for (front_q = visited->front; front_q; front_q = front_q->next)
	{
		if (((vertex_t *) front_q->ptr)->index == (size_t) x)
		{
			make_path(path, (vertex_t *) front_q->ptr);
			x = ((vertex_t *) front_q->ptr)->x;
		}
	}

	free_list_unvisited_visited(list_ver, unvisited, visited, path);
	return (path);
}
