#include "so_long.h"

char *read_all(int fd)
{
    char    buf[4096];
    int     r;
    char    *out = NULL;
    int     out_len = 0;

    while ((r = read(fd, buf, sizeof(buf))) > 0)
    {
        char *new_out = malloc(out_len + r + 1);
        if (!new_out)
            return (free(out), NULL);
        for (int i = 0; i < out_len; i++)
            new_out[i] = out[i];
        for (int i = 0; i < r; i++)
            new_out[out_len + i] = buf[i];
        new_out[out_len + r] = '\0';
        free(out);
        out = new_out;
        out_len += r;
    }
    return out;
}

void movies_string(t_game *params)
{
    char *temp;
    char *new_str;

    temp = ft_itoa(params->moves);
    if (!temp)
        return;
    new_str = ft_strjoin("MOVES: ", temp);
    free(temp);
    if (!new_str)
        return;
    free(params->moves_str);
    params->moves_str = new_str;
}

int handle_close(void *params)
{
    t_game *g = (t_game *) params;
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
    mlx_destroy_window(g->mlx , g->win);
    mlx_destroy_display(g->mlx);
    free(g->map);
    free(g->mlx);
    exit(0);
    return(0);
}

int loop_master(void *params)
{
    t_game *g = (t_game *)params;
    if (ft_strcmp(g->state, "RUNING") == 0)
    {
        animate_player(g);  
        game_loop(g);
        draw_map(g);
    }
    else
    {
        draw_last_window(g);
    }
    return (0);
}
