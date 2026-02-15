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

int handle_close(void *params)
{
    t_game *g = (t_game *) params;
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
    exit(0);
    return(0);
}
