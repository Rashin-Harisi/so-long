/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 route_validation.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: rabdolho <rabdolho@student.42vienna.c		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/24 13:09:37 by rabdolho		   #+#	  #+#			  */
/*	 Updated: 2026/02/24 13:14:49 by rabdolho		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "so_long.h"

static int	rout_fail(t_queue *q, char *map)
{
	if (q)
		queue_free(q);
	free(map);
	return (0);
}

static char	*rout_fail_map(t_queue *q, char *map)
{
	if (q)
		queue_free(q);
	free(map);
	return (NULL);
}

static int	push_neighbor(t_game *params, char *map, int x, int y)
{
	if (check_neghbors(params, map, x + 1, y)
		&& !queue_push(params->queue, x + 1, y))
		return (0);
	if (check_neghbors(params, map, x, y + 1)
		&& !queue_push(params->queue, x, y + 1))
		return (0);
	if (check_neghbors(params, map, x - 1, y)
		&& !queue_push(params->queue, x - 1, y))
		return (0);
	if (check_neghbors(params, map, x, y - 1)
		&& !queue_push(params->queue, x, y - 1))
		return (0);
	return (1);
}

static char	*route_init(t_game *params)
{
	char	*map;

	params->reach_c = 0;
	params->reach_e = 0;
	map = ft_strdup(params->map);
	if (!map)
		return (NULL);
	params->queue = queue_create(params->map_w * params->map_h);
	if (!params->queue)
		return (rout_fail_map(NULL, map));
	return (map);
}

int	valid_route(t_game *params)
{
	char	*map;
	int		x;
	int		y;

	if (!params || !params->map)
		return (0);
	map = route_init(params);
	if (!map)
		return (0);
	if (!queue_push(params->queue, params->player_x, params->player_y))
		return (rout_fail(params->queue, map));
	while (queue_pop(params->queue, &x, &y))
	{
		if (x < 0 || y < 0 || x >= params->map_w || y >= params->map_h)
			continue ;
		if (!visit_tile(map, params, x, y))
			continue ;
		if (!push_neighbor(params, map, x, y))
			return (rout_fail(params->queue, map));
	}
	queue_free(params->queue);
	params->queue = NULL;
	free(map);
	return (params->reach_c == params->collectibles && params->reach_e);
}
