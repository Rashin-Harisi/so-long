#include "so_long.h"

static void draw_tile(t_game *g , int i, int x, int y)
{
    
    if (g->map[i] == 'E' && g->collectibles == 0)
            mlx_put_image_to_window(g->mlx, g->win, g->floor_exit, x * TILE, y * TILE);
        else
            mlx_put_image_to_window(g->mlx, g->win, g->floor, x * TILE, y * TILE);

        if (g->map[i] == '1')
        {
            if (x == 0 || y == 0 || x == g->map_w -1 || y == g->map_h -1)
                mlx_put_image_to_window(g->mlx, g->win, g->wall, x * TILE, y * TILE);
            else
                 mlx_put_image_to_window(g->mlx, g->win, g->green_wall, x * TILE, y * TILE);
        }
        if (g->map[i] == 'C')
            mlx_put_image_to_window(g->mlx, g->win, g->collections, x * TILE , y *TILE);
}

void draw_map(t_game *g)
{
    int x = 0;
    int y = 0;
    int i = 0;
    while (g->map[i])
    {
        if (g->map[i] == '\n')
        {
            y++;
            x = 0;
            i++;
            continue;
        }
        draw_tile(g, i, x , y);
        x++;
        i++;
    }
    mlx_put_image_to_window(g->mlx, g->win, g->player_frames[g->current_frame], g->player_x * TILE, g->player_y * TILE);
    mlx_put_image_to_window(g->mlx, g->win, g->enemy , g->enemy_x * TILE, g->enemy_y * TILE);
    mlx_string_put(g->mlx, g->win, 10, 20 , 0xFFFFFF ,g->moves_str);
    mlx_string_put(g->mlx, g->win, 11, 20 , 0xFFFFFF ,g->moves_str);
    mlx_string_put(g->mlx, g->win, 10, 21 , 0xFFFFFF ,g->moves_str);
}