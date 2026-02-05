#include "so_long.h"


void draw_map(t_game *g)
{
    int x = 0;
    int y = 0;
    mlx_clear_window(g->mlx, g->win);
    for (int i = 0; g->map[i]; i++)
    {
        if (g->map[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        mlx_put_image_to_window(g->mlx, g->win, g->floor, x * TILE, y * TILE);

        if (g->map[i] == '1')
        {
            if (x == 0 || y == 0 || x == g->map_w -1 || y == g->map_h -1)
                mlx_put_image_to_window(g->mlx, g->win, g->wall, x * TILE, y * TILE);
            else
                 mlx_put_image_to_window(g->mlx, g->win, g->green_wall, x * TILE, y * TILE);
        }        
        x++;
    }
    mlx_put_image_to_window(g->mlx, g->win, g->player_frames[g->current_frame], g->player_x * TILE, g->player_y * TILE);
}