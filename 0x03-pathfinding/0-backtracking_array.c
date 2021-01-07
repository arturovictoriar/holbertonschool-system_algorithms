#include "pathfinding.h"
/**
 * free_start_target - free the copy of the start and target point
 * @s: start point
 * @t: target point
 * Return: Nothing
 */
void free_start_target(point_t *s, point_t *t)
{
	free(s);
	free(t);
}

/**
 * free_map - free the copy of the map
 * @c_map: copy of the map
 * @rows: number of rows that have the map
 * Return: Nothing
 */
void free_map(char **c_map, int rows)
{
	int i = 0;

	while (i < rows)
	{
		free(c_map[i]);
		i++;
	}
	free(c_map);
}

/**
 * make_path - build a queue representation of the path
 * @p: paht queue
 * @x: horizontal coordinate
 * @y: vertical coordinate
 * Return: 1 on success, 0 otherwise
 */
int make_path(queue_t *p, int x, int y)
{
	point_t *coor_p = NULL;

	coor_p = calloc(1, sizeof(point_t));
	coor_p->x = x;
	coor_p->y = y;
	queue_push_front(p, (void *) coor_p);

	return (1);
}

/**
 * find_path_recursive - find a path from start to target using backtracking
 * @map: representation of a maze where 1 is block way and 0 is a walkable way
 * @rows: number of rows
 * @cols: number of columns
 * @s: start point
 * @t: target point
 * @p: paht queue
 * Return: 1 on success, 0 otherwise
 */
int find_path_recursive(char **map, int rows, int cols,
		point_t *s, point_t *t, queue_t *p)
{
	int x = s->x, y = s->y;

	printf("Checking coordinates [%d, %d]\n", x, y);

	if (x == t->x && y == t->y)
		return (make_path(p, x, y));

	if (x >= cols || y >= rows || map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	if (x + 1 < cols && map[y][x + 1] == '0')
	{
		s->x++;
		if (find_path_recursive(map, rows, cols, s, t, p))
			return (make_path(p, x, y));
		s->x--;
	}
	if (y + 1 < rows && map[y + 1][x] == '0')
	{
		s->y++;
		if (find_path_recursive(map, rows, cols, s, t, p))
			return (make_path(p, x, y));
		s->y--;
	}
	if (x - 1 >= 0 && map[y][x - 1] == '0')
	{
		s->x--;
		if (find_path_recursive(map, rows, cols, s, t, p))
			return (make_path(p, x, y));
		s->x++;
	}
	if (y - 1 >= 0 && map[y - 1][x] == '0')
	{
		s->y--;
		if (find_path_recursive(map, rows, cols, s, t, p))
			return (make_path(p, x, y));
		s->y++;
	}

	return (0);
}

/**
 * backtracking_array - find a path from start to target using backtracking
 * @map: representation of a maze where 1 is block way and 0 is a walkable way
 * @rows: number of rows
 * @cols: number of columns
 * @start: start point
 * @target: target point
 * Return: a queue path on success, NULL otherwise
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target)
{
	queue_t *path = NULL;
	point_t *s = NULL, *t = NULL;
	char **c_map = NULL;
	int i = 0, j = 0;

	c_map = calloc(rows, sizeof(char *));
	while (i < rows)
	{
		c_map[i] = calloc(cols, sizeof(char));
		i++;
	}

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			c_map[i][j] = map[i][j];
			j++;
		}
		i++;
	}

	s = calloc(1, sizeof(point_t));
	t = calloc(1, sizeof(point_t));
	s->x = start->x, s->y = start->y, t->x = target->x, t->y = target->y;

	path = queue_create();
	if (!find_path_recursive(c_map, rows, cols, s, t, path))
	{
		free_start_target(s, t);
		free_map(c_map, rows);
		queue_delete(path);
		return (NULL);
	}
	free_start_target(s, t);
	free_map(c_map, rows);

	return (path);
}
