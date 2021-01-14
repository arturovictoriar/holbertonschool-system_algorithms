#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graphs.h"
#include "queues.h"

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
 * struct a_start_s - Structure node representing a vertece
 *
 * @index: Index of the vertex in the adjency list.
 *   When a new vertex is added, this index becomes the number of vertices
 *   in the adjency list before it is added.
 * @content: Custom data stored in the vertex (here, a string)
 * @x: Vertex X coordinate
 * @y: Vertex Y coordinate
 * @edges: Pointer to the head node of the linked list of edges
 * @parent: parent node
 * @distance: min distance from node to node
 * @heuristic: euclidian distance from current node to target node
 * @visited: check if the node has been visited
 * @cost_path: the addition between distace and heuristic
 */
typedef struct a_start_s
{
	size_t		index;
	char		*content;
	int		x;
	int		y;
	edge_t		*edges;
	int		parent;
	int		distance;
	int		heuristic;
	char		visited;
	int		cost_path;
} a_start_t;


queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target);

queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target);

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target);

queue_t *a_star_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target);

#endif
