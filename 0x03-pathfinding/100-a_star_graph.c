#include "pathfinding.h"
#include <string.h>

/**
 * free_list_unvisited_visited - free all the memory allocated
 * @list_h: list of visited vertices
 * @unvisited: queue of unvisited vertices
 * @visited: queue of visited vertices
 * @path: queue of path from start to target
 * Return: Nothing
 */
void free_list_unvisited_visited(a_start_t *list_h, queue_t *unvisited,
		queue_t *visited, queue_t *path)
{
	free(list_h);
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
int make_path(queue_t *p, a_start_t *v)
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
queue_node_t *find_node_queue(queue_t *unvisited, a_start_t *neighbor)
{
	queue_node_t *front = NULL;

	front = unvisited->front;
	while (front)
	{
		if (((vertex_t *) front->ptr)->index == neighbor->index)
			break;
		front = front->next;
	}

	return (front);
}

/**
 * a_start_algo - A* algoritm applied on graph
 * @start: start vertice
 * @target: target vertice
 * @visited: queue of visited vertices
 * @unvisited: queue of unvisited vertices
 * @list_h: list of vertices visited
 * Return: a vertex pointer with the target vertice
 */
a_start_t *a_start_algo(a_start_t *start, a_start_t *target, queue_t *visited,
		queue_t *unvisited, a_start_t *list_h)
{
	a_start_t *visiting = start, *node = NULL;
	edge_t *neighbors = NULL;
	queue_node_t *node_q = NULL;
	int parent = 0;
	void *c_ptr = NULL;

	for (visiting->distance = 0; visiting;)
	{
		printf("Checking %s, distance to %s is %d\n", visiting->content,
				target->content, visiting->heuristic);
		if (visiting->index == target->index)
			break;
		visiting->visited = '1', neighbors = visiting->edges;
		for (node_q = NULL; neighbors; node_q = NULL, neighbors = neighbors->next)
		{
			node = &(list_h[neighbors->dest->index]);
			if ((node->visited == '0') &&
					((node->distance > (visiting->distance + neighbors->weight)) ||
					 (node->distance == -1)))
			{
				parent = node->parent, node->parent = visiting->index;
				node->distance = visiting->distance + neighbors->weight;
				node->cost_path = node->distance + node->heuristic;
				if (parent == -1)
					node_q = queue_push_back(unvisited, (void *) node);
				else
					node_q = find_node_queue(unvisited, node);
			}
			while (node_q && node_q->prev &&
					(((a_start_t *) node_q->prev->ptr)->cost_path >
					 ((a_start_t *) node_q->ptr)->cost_path))
			{
				c_ptr = node_q->prev->ptr, node_q->prev->ptr = node_q->ptr;
				node_q->ptr = c_ptr, node_q = node_q->prev;
			}
		}
		queue_push_front(visited, (void *) visiting);
		visiting = (a_start_t *) dequeue(unvisited);
	}
	return (visiting);
}

/**
 * a_star_graph - find a path from start to target using A* in graph
 * @graph: representation of a complete graph vertices
 * @start: start point
 * @target: target point
 * Return: a queue path on success, NULL otherwise
 */
queue_t *a_star_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	queue_t *path = NULL, *unvisited = NULL, *visited = NULL;
	queue_node_t *front_q = NULL;
	vertex_t *all_v = NULL;
	a_start_t *list_h = NULL, *visiting = NULL;
	size_t i = 0;
	int parent = 0;

	list_h = calloc(graph->nb_vertices, sizeof(a_start_t));
	for (all_v = graph->vertices; all_v; all_v = all_v->next)
	{
		i = all_v->index;
		list_h[i].parent = -1, list_h[i].distance = -1, list_h[i].heuristic = -1;
		list_h[i].index = all_v->index, list_h[i].content = all_v->content;
		list_h[i].x = all_v->x, list_h[i].y = all_v->y, list_h[i].cost_path = -1;
		list_h[i].edges = all_v->edges, list_h[i].visited = '0';
		list_h[i].heuristic = sqrt(pow(all_v->x - target->x, 2) +
			pow(all_v->y - target->y, 2));
	}

	(path = queue_create(), unvisited = queue_create(), visited = queue_create());
	visiting = a_start_algo(&(list_h[start->index]), &(list_h[target->index]),
			visited, unvisited, list_h);
	if (!visiting)
	{
		free_list_unvisited_visited(list_h, unvisited, visited, path);
		return (NULL);
	}

	make_path(path, visiting);
	parent = visiting->parent;
	for (front_q = visited->front; front_q; front_q = front_q->next)
	{
		if (((a_start_t *) front_q->ptr)->index == (size_t) parent)
		{
			make_path(path, (a_start_t *) front_q->ptr);
			parent = ((a_start_t *) front_q->ptr)->parent;
		}
	}
	free_list_unvisited_visited(list_h, unvisited, visited, path);
	return (path);
}
