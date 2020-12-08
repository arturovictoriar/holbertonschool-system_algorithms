#include "graphs.h"

/**
 * free_q - frees a queue
 * @queue: queue pointer
 */
void free_q(queue_t *queue)
{
	node_t *node, *node_temp;

	node = queue->head;
	while (queue->size > 0)
	{
		node_temp = node;
		node = node->next;
		free(node_temp);
	}
	free(queue);
}

/**
 * push - pushe a node in queue
 * @queue: pointer of queue
 * @vertex: pointer of vertex
 * @depth: deep of vertex
 * Return: 1 on success, 0 otherwise
 */
int push(queue_t *queue, vertex_t *vertex, size_t depth)
{
	node_t *node;

	node = malloc(sizeof(node_t));
	if (!node)
		return (free_q(queue), 0);

	node->vertex = vertex, node->depth = depth;

	if (!queue->tail)
		queue->tail = queue->head = node;
	else
		queue->tail->next = node, queue->tail = node;

	queue->size++;
	return (1);
}

/**
 * pop - pop a node from head of queue
 * @queue: queue pointer
 * @vertex: vertex pointer
 * @depth: depth of vertex
 * Return: 1 on success, 0 otherwise
 */
int pop(queue_t *queue, vertex_t **vertex, size_t *depth)
{
	node_t *node;

	if (!queue || !queue->head)
		return (0);

	node = queue->head, queue->head = queue->head->next;

	if (!queue->head)
		queue->tail = NULL;

	*vertex = node->vertex, queue->size--, *depth = node->depth;

	free(node);

	return (1);
}

/**
 * breadth_first_traverse - BFS
 * @graph: pointer to graph object
 * @action: pointer to traverse function
 * Return: max depth
 */
size_t breadth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	queue_t *queue = NULL;
	vertex_t *node_vertex = NULL;
	edge_t *edge = NULL;
	size_t max_depth = 0, node_depth = 0;
	size_t i = 0, size_q = 0;
	char len_gra[2048] = {0};

	if (!graph || !action || !graph->nb_vertices)
		return (0);
	queue = calloc(1, sizeof(queue_t));
	if (!queue)
		return (0);
	len_gra[graph->vertices->index] = 1;
	push(queue, graph->vertices, 0);
	while (queue->size)
	{
		for (i = 0, size_q = queue->size; i < size_q; i++)
		{
			pop(queue, &node_vertex, &node_depth);
			action(node_vertex, node_depth);
			max_depth = max_depth > node_depth ? max_depth : node_depth;
			for (edge = node_vertex->edges; edge; edge = edge->next)
			{
				if (len_gra[edge->dest->index])
					continue;
				len_gra[edge->dest->index] = 1;
				if (!push(queue, edge->dest, node_depth + 1))
					return (0);
			}
		}
	}
	free_q(queue);
	return (max_depth);
}
