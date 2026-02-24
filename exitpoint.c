/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitpoint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:31:53 by rabdolho          #+#    #+#             */
/*   Updated: 2026/02/24 12:33:15 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	find_exit_point(t_game *g)
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
		if (g->map[i] == 'E')
		{
			g->exit_x = x;
			g->exit_y = y;
			return ;
		}
		x++;
		i++;
	}
}
