/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_last_window.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: rabdolho <rabdolho@student.42vienna.c		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/24 11:54:08 by rabdolho		   #+#	  #+#			  */
/*	 Updated: 2026/02/24 11:57:59 by rabdolho		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "so_long.h"

void	draw_last_window(t_game *g)
{
	long	now;

	now = time_now();
	if (ft_strncmp(g->state, "WIN", ft_strlen("WIN")) == 0)
	{
		mlx_put_image_to_window(g->mlx, g->last_win, g->winer, 41, 25);
		mlx_string_put(g->mlx, g->last_win, 120, 60, 0x0000FF00, "HORAAAAAA");
		mlx_string_put(g->mlx, g->last_win, 121, 60, 0x0000FF00, "HORAAAAAA");
		mlx_string_put(g->mlx, g->last_win, 120, 61, 0x0000FF00, "HORAAAAAA");
		if (now - g->end_time >= 5000)
			handle_close(g);
	}
	if (ft_strncmp(g->state, "LOSE", ft_strlen("LOSE")) == 0)
	{
		mlx_put_image_to_window(g->mlx, g->last_win, g->loser, 40, 25);
		mlx_string_put(g->mlx, g->last_win, 120, 60, 0x00FF0000, "GAME OVER");
		mlx_string_put(g->mlx, g->last_win, 121, 60, 0x00FF0000, "GAME OVER");
		mlx_string_put(g->mlx, g->last_win, 120, 61, 0x00FF0000, "GAME OVER");
		if (now - g->end_time >= 5000)
			handle_close(g);
	}
}
