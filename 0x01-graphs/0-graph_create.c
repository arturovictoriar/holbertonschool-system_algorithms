#include "graphs.h"

/**
 * graph_create - create a graph structure
 * Return: a graph pointer on succes, NULL otherwise
 */
graph_t *graph_create(void)
{
	graph_t *new_g = NULL;

	new_g = malloc(sizeof(graph_t));
	if (!new_g)
		return (NULL);

	new_g->nb_vertices = 0;
	new_g->vertices = NULL;

	return (new_g);
}
