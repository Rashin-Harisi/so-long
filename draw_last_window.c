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
		mlx_put_image_to_window(g->mlx, g->last_win, g->winer, 30, 20);
		if (now - g->end_time >= 5000)
			handle_close(g);
	}
	if (ft_strncmp(g->state, "LOSE", ft_strlen("LOSE")) == 0)
	{
		mlx_put_image_to_window(g->mlx, g->last_win, g->loser, 30, 20);
		if (now - g->end_time >= 5000)
			handle_close(g);
	}
}
