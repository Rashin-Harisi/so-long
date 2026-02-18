#include "so_long.h"

void draw_last_window(t_game *g)
{
    long now;
    now = time_now();
    if (ft_strcmp(g->state,"WIN") == 0)
    {
        mlx_put_image_to_window(g->mlx, g->last_win, g->winer, 0, 0);
        if (now - g->end_time >= 5000)
            handle_close(g);
    }
    if (ft_strcmp(g->state, "LOSE") == 0)
    {
        mlx_put_image_to_window(g->mlx, g->last_win, g->loser, 0, 0);
        if (now - g->end_time >= 5000)
            handle_close(g);
    }
}