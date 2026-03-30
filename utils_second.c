/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:55:56 by rabdolho          #+#    #+#             */
/*   Updated: 2026/03/09 11:56:00 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int check_arguments(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Error\nThe correct form is ./so_long map.ber\n");
        return (0);
    }
    if (!is_ber_map(argv[1]))
    {
        ft_printf("Error\nThe map formap is invalid\n");
        return (0);
    }
    return (1);
}

void    destroy_images(t_game *g)
{
    if (g->floor)
        mlx_destroy_image(g->mlx, g->floor);
    if (g->floor_exit)
        mlx_destroy_image(g->mlx, g->floor_exit);
    if (g->wall)
        mlx_destroy_image(g->mlx, g->wall);
    if (g->green_wall)
        mlx_destroy_image(g->mlx, g->green_wall);
    if (g->collections)
        mlx_destroy_image(g->mlx, g->collections);
    if (g->player_frames[0])
        mlx_destroy_image(g->mlx, g->player_frames[0]);
    if (g->player_frames[1])
        mlx_destroy_image(g->mlx, g->player_frames[1]);
    if (g->player_frames[2])
        mlx_destroy_image(g->mlx, g->player_frames[2]);
    if (g->player_frames[3])
        mlx_destroy_image(g->mlx, g->player_frames[3]);
    if (g->winer)
        mlx_destroy_image(g->mlx, g->winer);
    if (g->enemy)
        mlx_destroy_image(g->mlx, g->enemy);
    if (g->loser)
        mlx_destroy_image(g->mlx, g->loser);
}

void    destroy_windows(t_game *g)
{
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->last_win)
        mlx_destroy_window(g->mlx, g->last_win);
    if (g->mlx)
    {
        mlx_destroy_display(g->mlx);
        free(g->mlx);
    }
}
