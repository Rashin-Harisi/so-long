/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 enemy.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: rabdolho <rabdolho@student.42vienna.c		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/24 12:17:26 by rabdolho		   #+#	  #+#			  */
/*	 Updated: 2026/02/24 12:21:52 by rabdolho		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "so_long.h"

static void	add_neighboar(t_game *params, int x, int y)
{
	if (params->enemy_var.count >= 4)
		return ;
	if (!check_neghbors_enemy(params, x, y))
		return ;
	if (params->prev_enemy_x == x && params->prev_enemy_y == y)
		return ;
	params->enemy_var.n[params->enemy_var.count].x = x;
	params->enemy_var.n[params->enemy_var.count].y = y;
	params->enemy_var.count++;
}

static void	move_enemy(t_game *g)
{
	int	index;

	if (g->enemy_var.count == 0)
		return ;
	if (g->enemy_var.num < 70)
		update_enemy_location(g, g->enemy_var.n, g->enemy_var.count);
	else
	{
		index = rand() % g->enemy_var.count;
		g->enemy_x = g->enemy_var.n[index].x;
		g->enemy_y = g->enemy_var.n[index].y;
	}
}

static void	initial_values(t_game *params)
{
	params->enemy_var.count = 0;
	params->enemy_var.num = rand() % 100;
	params->enemy_var.old_x = params->enemy_x;
	params->enemy_var.old_y = params->enemy_y;
	params->enemy_var.now = time_now();
}

int	game_loop(t_game *params)
{
	long	now;

	now = time_now();
	if (ft_strncmp(params->state, "RUNING", ft_strlen("RUNING")) != 0)
		return (0);
	if (now - params->last_enemy_ms < 500)
		return (0);
	initial_values(params);
	add_neighboar(params, params->enemy_x + 1, params->enemy_y);
	add_neighboar(params, params->enemy_x - 1, params->enemy_y);
	add_neighboar(params, params->enemy_x, params->enemy_y + 1);
	add_neighboar(params, params->enemy_x, params->enemy_y - 1);
	move_enemy(params);
	params->prev_enemy_x = params->enemy_var.old_x;
	params->prev_enemy_y = params->enemy_var.old_y;
	if (game_over(params))
	{
		params->state = "LOSE";
		params->end_time = time_now();
		if (!params->last_win)
			params->last_win = mlx_new_window(params->mlx, 300, 300, "end");
		return (0);
	}
	params->last_enemy_ms = params->enemy_var.now;
	params->needs_redraw = 1;
	return (0);
}
