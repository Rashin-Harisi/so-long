/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:03:11 by rabdolho          #+#    #+#             */
/*   Updated: 2026/02/25 12:03:20 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

long	time_now(void)
{
	struct timeval	tv;
	long			now;

	now = 0;
	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (now);
}

int	create_window(t_game *g)
{
	g->win = mlx_new_window(g->mlx, g->map_w * TILE,
			g->map_h * TILE, "so_long");
	if (!g->win)
	{
		free(g->map);
		return (0);
	}
	return (1);
}

int	visit_tile(char *map, t_game *params, int x, int y)
{
	int	index;
	int	map_w;

	map_w = params->map_w;
	if (!map)
		return (0);
	index = y * (map_w + 1) + x;
	if (map[index] == '1' || map[index] == 'V'
		|| map[index] == '\n' || map[index] == '\0')
		return (0);
	if (map[index] == 'C')
		params->reach_c++;
	else if (map[index] == 'E')
		params->reach_e = 1;
	map[index] = 'V';
	return (1);
}

int	check_neghbors(t_game *params, char *map, int x, int y)
{
	int	index;

	if (!map)
		return (0);
	if (x < 0 || x >= params->map_w
		|| y < 0 || y >= params->map_h)
		return (0);
	index = y * (params->map_w + 1) + x;
	if (map [index] == '1' || map[index] == 'V'
		|| map [index] == '\n' || map[index] == '\0'
		|| map[index] == 'Q')
		return (0);
	if (map[index] != 'C' && map[index] != 'E')
		map[index] = 'Q';
	return (1);
}

int	is_ber_map(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (ft_strncmp((str + (len - 4)), ".ber", 4) == 0)
		return (1);
	return (0);
}