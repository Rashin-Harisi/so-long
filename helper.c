/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:36:44 by rabdolho          #+#    #+#             */
/*   Updated: 2026/02/24 12:43:52 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

char	*read_all(int fd)
{
	char	buf[4096];
	int		r;
	char	*out;
	int		out_len;
	int		i;
	char	*new_out;

	out = NULL;
	out_len = 0;
	i = -1;
	r = read(fd, buf, sizeof(buf));
	while (r > 0)
	{
		new_out = malloc(out_len + r + 1);
		if (!new_out)
			return (free(out), NULL);
		while (++i < out_len)
			new_out[i] = out[i];
		i = -1;
		while (++i < r)
			new_out[out_len + i] = buf[i];
		new_out[out_len + r] = '\0';
		free(out);
		out = new_out;
		out_len += r;
	}
	return (out);
}

void	movies_string(t_game *params)
{
	char	*temp;
	char	*new_str;

	temp = ft_itoa(params->moves);
	if (!temp)
		return ;
	new_str = ft_strjoin("MOVES: ", temp);
	free(temp);
	if (!new_str)
		return ;
	free(params->moves_str);
	params->moves_str = new_str;
}

int	handle_close(void *params)
{
	t_game	*g;

	g = (t_game *) params;
	free(g->moves_str);
	g->moves_str = NULL;
	mlx_destroy_image(g->mlx, g->floor);
	mlx_destroy_image(g->mlx, g->floor_exit);
	mlx_destroy_image(g->mlx, g->wall);
	mlx_destroy_image(g->mlx, g->green_wall);
	mlx_destroy_image(g->mlx, g->collections);
	mlx_destroy_image(g->mlx, g->player_frames[0]);
	mlx_destroy_image(g->mlx, g->player_frames[1]);
	mlx_destroy_image(g->mlx, g->player_frames[2]);
	mlx_destroy_image(g->mlx, g->player_frames[3]);
	mlx_destroy_image(g->mlx, g->enemy);
	mlx_destroy_image(g->mlx, g->winer);
	mlx_destroy_image(g->mlx, g->loser);
	mlx_destroy_window(g->mlx, g->win);
	if (g->last_win)
		mlx_destroy_window(g->mlx, g->last_win);
	mlx_destroy_display(g->mlx);
	free(g->map);
	free(g->mlx);
	exit(0);
	return (0);
}

int	loop_master(void *params)
{
	t_game	*g;

	g = (t_game *)params;
	if (ft_strncmp(g->state, "RUNING", ft_strlen("RUNING")) == 0)
	{
		animate_player(g);
		game_loop(g);
		if (g->needs_redraw)
		{
			draw_map(g);
			g->needs_redraw = 0;
		}
	}
	else
	{
		draw_last_window(g);
	}
	return (0);
}

int	fail_validation(t_game *g)
{
	free(g->map);
	g->map = NULL;
	ft_printf("Error\n");
	return (0);
}
