#include "so_long.h"


int handle_key(int keycode, void *params)
{
    t_game *g = (t_game *)params;
    int new_x = g->player_x;
    int new_y = g->player_y;
    int index;
    if (ft_strcmp(g->state,"RUNING") != 0)
        return (0);
    if (keycode == 65307) //ESC keycode
        return (handle_close(g), 0);
    else if (keycode == 119 || keycode == 65362) //UP
        new_y--;
    else if (keycode == 115 || keycode == 65364) //DOWN
        new_y++;
    else if (keycode == 97 || keycode == 65361) //LEFT
        new_x--;
    else if (keycode == 100 || keycode == 65363) //RIGHT
        new_x++;

    if (new_x == g->player_x && new_y == g->player_y) //no movement
        return (0);
    if (new_x < 0 || new_y < 0 || new_x >= g->map_w || new_y >= g->map_h)
        return (0);
    index = new_y * (g->map_w + 1) + new_x;
    if (g->map[index] == '1') //wall encounter
        return (0);
    if (g->map[index] == 'C')
    {
        g->collectibles--;
        g->map[index] = '0';
    }
    if (new_x == g->exit_x && new_y == g->exit_y && g->collectibles == 0)
    {
            g->state = "WIN";
            g->end_time = time_now();
            g->last_win = mlx_new_window(g->mlx, 700, 700 , "end");
            if (!g->last_win) return (free(g->map), 1);
    }
    g->player_x = new_x;
    g->player_y = new_y;
    g->moves++;
    movies_string(g);
    printf("moves : %d\n", g->moves);
    draw_map(g);
    return (0);
}
