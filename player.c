/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:04:50 by rabdolho          #+#    #+#             */
/*   Updated: 2026/02/24 13:09:21 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	animate_player(void *param)
{
	t_game		*game;
	static long	last;
	long		now;

	game = (t_game *)param;
	if (ft_strncmp(game->state, "RUNING", 6) != 0)
		return (0);
	now = time_now();
	if (now - last < 120)
		return (0);
	last = now;
	game->current_frame = (game->current_frame + 1) % PLAYER_FRAMES;
	game->needs_redraw = 1;
	return (0);
}

void	find_player_position(t_game *g)
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
		if (g->map[i] == 'P')
		{
			g->player_x = x;
			g->player_y = y;
			return ;
		}
		x++;
		i++;
	}
}

int	draw_player(t_game *g, int *w, int *h)
{
	g->player_frames[0] = mlx_xpm_file_to_image(g->mlx,
			"texture/player.xpm", w, h);
	if (!g->player_frames[0] || *w != TILE || *h != TILE)
		return (0);
	g->player_frames[1] = mlx_xpm_file_to_image(g->mlx,
			"texture/player_1.xpm", w, h);
	if (!g->player_frames[1] || *w != TILE || *h != TILE)
		return (0);
	g->player_frames[2] = mlx_xpm_file_to_image(g->mlx,
			"texture/player_2.xpm", w, h);
	if (!g->player_frames[2] || *w != TILE || *h != TILE)
		return (0);
	g->player_frames[3] = mlx_xpm_file_to_image(g->mlx,
			"texture/player_3.xpm", w, h);
	if (!g->player_frames[3] || *w != TILE || *h != TILE)
		return (0);
	return (1);
}
