#include "so_long.h"


int handle_key(int keycode, void *params)
{
    t_game *g = (t_game *)params;
    int new_x = g->player_x;
    int new_y = g->player_y;

    if (keycode == 65307) //ESC keycode
    {
        mlx_destroy_window(g->mlx, g->win);
        free(g->map);
        exit(0);
    }
    else if (keycode == 65362 || keycode == 122) //UP
        new_y--;
    else if (keycode == 65364 || keycode == 115) //DOWN
        new_y++;
    else if (keycode == 65361 || keycode == 113) //LEFT
        new_x--;
    else if (keycode == 65363 || keycode == 100) //RIGHT
        new_x++;

    if (new_x == g->player_x && new_y == g->player_y) //no movement
        return (0);
    if (g->map[new_y * (g->map_w + 1) + new_x] == '1') //wall encounter
        return (0);
    
    g->player_x = new_x;
    g->player_y = new_y;
    g->moves++;
    printf("moves : %d\n", g->moves);
    draw_map(g);
    return (0);
}
