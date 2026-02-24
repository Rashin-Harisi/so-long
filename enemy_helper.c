/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 enemy_helper.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: rabdolho <rabdolho@student.42vienna.c		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/24 12:22:16 by rabdolho		   #+#	  #+#			  */
/*	 Updated: 2026/02/24 12:30:57 by rabdolho		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "so_long.h"

void	find_enemy_position(t_game *g)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	while (g->map[i])
	{
		if (g->map[i] == '\n')
		{
			y++;
			x = 0;
			i++;
			continue ;
		}
		if (g->map[i] == 'X')
		{
			g->enemy_x = x;
			g->enemy_y = y;
			return ;
		}
		x++;
		i++;
	}
}

long	time_now(void)
{
	struct timeval	tv;
	long			now;

	now = 0;
	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (now);
}

int	check_neghbors_enemy(t_game *params, int x, int y)
{
	int	index;

	if (!params || !params->map)
		return (0);
	if (x < 0 || x >= params->map_w
		|| y < 0 || y >= params->map_h)
		return (0);
	index = y * (params->map_w + 1) + x;
	if (params->map[index] == '1' || params->map[index] == '\n'
		|| params->map[index] == '\0')
		return (0);
	return (1);
}

void	update_enemy_location(t_game *params, t_neighbor n[], int count)
{
	int	i;
	int	new_x;
	int	new_y;
	int	min;

	i = 0;
	new_x = params->enemy_x;
	new_y = params->enemy_y;
	min = INT_MAX;
	if (count == 0)
	{
		params->enemy_x = params->prev_enemy_x;
		params->enemy_y = params->prev_enemy_y;
		return ;
	}
	while (i < count)
	{
		if ((abs(n[i].x - params->player_x) + abs(n[i].y - params->player_y))
			< min)
		{
			min = (abs(n[i].x - params->player_x)
					+ abs(n[i].y - params->player_y));
			new_x = n[i].x;
			new_y = n[i].y;
		}
		i++;
	}
	params->enemy_x = new_x;
	params->enemy_y = new_y;
}

int	game_over(t_game *params)
{
	if (params->enemy_x == params->player_x
		&& params->enemy_y == params->player_y)
		return (1);
	return (0);
}
