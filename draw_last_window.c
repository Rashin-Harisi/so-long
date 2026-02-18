#include "so_long.h"

void draw_last_window(t_game *g)
{
    long now;
    now = time_now();
    if (ft_strncmp(g->state,"WIN", ft_strlen("WIN")) == 0)
    {
        mlx_put_image_to_window(g->mlx, g->last_win, g->winer, 41.5, 25);
        if (now - g->end_time >= 5000)
            handle_close(g);
    }
    if (ft_strncmp(g->state, "LOSE", ft_strlen("LOSE")) == 0)
    {
        mlx_put_image_to_window(g->mlx, g->last_win, g->loser, 40.5, 25);
        if (now - g->end_time >= 5000)
            handle_close(g);
    }
}