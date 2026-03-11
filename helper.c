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
	int		len;
	char	*temp;

	out = NULL;
	len = 0;
	while (1)
	{
		r = read(fd, buf, sizeof(buf));
		if (r <= 0)
			break ;
		temp = malloc(len + r + 1);
		if (!temp)
			return (free(out), NULL);
		while (out)
			ft_memcpy(temp, out, len);
		ft_memcpy(temp + len, buf, r);
		temp[len + r] = '\0';
		free(out);
		out = temp;
		len += r;
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

	g = (t_game *)params;
    if (g->moves_str)
        free(g->moves_str);
    if (g->map)
        free(g->map);
    if (g->mlx)
    {
        destroy_images(g);
        destroy_windows(g);
    }
    exit(0);
}

int	loop_master(void *params)
{
	t_game	*g;

	g = (t_game *)params;
	if (ft_strncmp(g->state, "RUNING", ft_strlen("RUNING")) == 0)
	{
		animate_player(g);
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

int	fail_validation(t_game *g, char *text)
{
	free(g->map);
	g->map = NULL;
	ft_printf("Error\n");
	ft_printf("%s\n", text);
	return (0);
}
