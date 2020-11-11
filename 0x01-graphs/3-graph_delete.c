#include "graphs.h"

/**
 * graph_delete - delete a graph structure
 * @graph: the graph struct
 * Return: nothing
 */
void graph_delete(graph_t *graph)
{
	vertex_t *cp_ve_header = NULL, *last_ve = NULL;
	edge_t *cp_ed_header = NULL, *last_ed = NULL;

	if (!graph)
		return;
	cp_ve_header = graph->vertices;
	while (cp_ve_header)
	{
		if (cp_ve_header->content)
			free(cp_ve_header->content);

		if (cp_ve_header->edges)
		{
			cp_ed_header = cp_ve_header->edges;
			while (cp_ed_header)
			{
				last_ed = cp_ed_header;
				cp_ed_header = cp_ed_header->next;
				free(last_ed);
			}
		}

		last_ve = cp_ve_header;
		cp_ve_header = cp_ve_header->next;
		free(last_ve);
	}
	free(graph);
}
