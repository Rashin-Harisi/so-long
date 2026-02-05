#include "so_long.h"


int main(void)
{
    t_game g;
    g.moves = 0;
    g.mlx = mlx_init();
    if (!g.mlx) return 1;

    int fd = open("map.ber", O_RDONLY);
    if (fd < 0) return 1;

    g.map = read_all(fd);
    close(fd);
    if (!g.map) return 1;

    int width = 0;
    while (g.map[width] && g.map[width] != '\n') width++;

    int height = 0;
    for (int i = 0; g.map[i]; i++)
        if (g.map[i] == '\n') height++;
    height += 1;

    g.map_w = width;
    g.map_h = height;
    find_player_position(&g);
    g.map[g.player_y * (g.map_w + 1) + g.player_x] = '0'; //omiting player from map

    g.win = mlx_new_window(g.mlx, width * TILE, height * TILE, "so_long map test");
    if (!g.win) return (free(g.map), 1);

    int w, h;
    g.player_frames[0] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[1] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player_1.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[2] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player_2.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[3] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player_3.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.current_frame = 0;

    
    g.wall = mlx_xpm_file_to_image(g.mlx, "texture and figure/wall.xpm", &w, &h);
    g.green_wall = mlx_xpm_file_to_image(g.mlx,"texture and figure/green_wall.xpm", &w, &h);
    g.floor = mlx_xpm_file_to_image(g.mlx, "texture and figure/floor.xpm", &w, &h);
    if (!g.wall || !g.green_wall || !g.floor || !g.player_frames[0] ||
        !g.player_frames[1] || !g.player_frames[2] || !g.player_frames[3])
        return (free(g.map), 1);
        
    mlx_loop_hook(g.mlx, animate_player, &g);
    mlx_key_hook(g.win, handle_key, &g);
    mlx_hook(g.win, 17, 0, handle_close, &g);

    draw_map(&g);
    mlx_loop(g.mlx);
    free(g.map);
    return 0;
}

