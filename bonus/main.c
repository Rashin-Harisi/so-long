/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:48:30 by rabdolho          #+#    #+#             */
/*   Updated: 2026/02/24 12:56:20 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

static int	draw_images(t_game *g, int *w, int *h)
{
	int	w_lose;
	int	w_win;
	int	h_lose;
	int	h_win;

	g->map[g->player_y * (g->map_w + 1) + g->player_x] = '0';
	if (!draw_player(g, w, h))
		return (0);
	g->wall = mlx_xpm_file_to_image(g->mlx, "texture/wall.xpm", w, h);
	g->green_wall = mlx_xpm_file_to_image(g->mlx, "texture/gwall.xpm", w, h);
	g->collections = mlx_xpm_file_to_image(g->mlx, "texture/collect.xpm", w, h);
	g->floor = mlx_xpm_file_to_image(g->mlx, "texture/floor.xpm", w, h);
	g->floor_exit = mlx_xpm_file_to_image(g->mlx,
			"texture/exit_floor.xpm", w, h);
	g->enemy = mlx_xpm_file_to_image(g->mlx, "texture/enemy.xpm", w, h);
	g->winer = mlx_xpm_file_to_image(g->mlx, "texture/win.xpm", &w_win, &h_win);
	g->loser = mlx_xpm_file_to_image(g->mlx,
			"texture/lose.xpm", &w_lose, &h_lose);
	if (!g->wall || !g->green_wall || !g->floor || !g->player_frames[0]
		|| !g->player_frames[1] || !g->player_frames[2] || !g->player_frames[3]
		|| !g->collections || !g->floor_exit || !g->enemy
		|| !g->winer || !g->loser)
		return (0);
	return (1);
}

static int	initial_setup(t_game *g)
{
	ft_bzero(g, sizeof(t_game));
	g->moves_str = NULL;
	g->state = "RUNING";
	movies_string(g);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (0);
	srand(time(NULL));
	return (1);
}

static int	reading_map(t_game *g, char *filename)
{
	int	fd;
	int	i;

	i = -1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	g->map = read_all(fd);
	close(fd);
	if (!g->map)
		return (0);
	g->map_w = 0;
	while (g->map[g->map_w] && g->map[g->map_w] != '\n')
		g->map_w++;
	g->map_h = 0;
	while (g->map[++i])
	{
		if (g->map[i] == '\n')
			g->map_h++;
	}
	g->map_h += 1;
	return (1);
}

int	map_validation(t_game *g)
{
	if (is_length_equal(g->map) == 0)
		return (fail_validation(g ,"Map is not rectangular."));
	if (is_map_rounded_closed(g->map, g->map_h) == 0)
		return (fail_validation(g, "Map is not rounded with walls."));
	if (valid_characters(g) == 0)
		return (fail_validation(g, "Map has not valid characters."));
	find_exit_point(g);
	find_player_position(g);
	find_enemy_position(g);
	if (valid_route(g) == 0)
		return (fail_validation(g, "Map has not valid routs for all collections."));
	return (1);
}

int	main(int argc, char **argv)
{
	int		w;
	int		h;
	t_game	g;

	if (argc != 2)
	{
		ft_printf("Error\nThe correct form is ./so_long map.ber\n");
		return (1);
	}
	if (!is_ber_map(argv[1]))
	{
		ft_printf("Error\nThe map formap is invalid\n");
		return (1);
	}
	if (!initial_setup(&g))
		return (1);
	if (!reading_map(&g, argv[1]) || !map_validation(&g) || !create_window(&g))
	{
		handle_close(&g);
		return (1);
	}
	if (!draw_images(&g, &w, &h))
	{
		handle_close(&g);
		return (1);
	}
	mlx_loop_hook(g.mlx, loop_master, &g);
	mlx_key_hook(g.win, handle_key, &g);
	mlx_hook(g.win, 17, 0, handle_close, &g);
	mlx_loop(g.mlx);
	free(g.map);
	free(g.moves_str);
	return (0);
}
