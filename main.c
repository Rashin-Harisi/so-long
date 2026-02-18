#include "so_long.h"


int main(void)
{
    int w, h;
    t_game g;
    ft_bzero(&g, sizeof(t_game));
    g.moves_str = NULL;
    g.state = "RUNING";
    movies_string(&g);
    g.mlx = mlx_init();
    if (!g.mlx) return 1;
    srand(time(NULL));
    int w_lose;
    int w_win;
    int h_lose;
    int h_win;
    //////////////////////////////////reading map
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
    /////////////////map validation
    if(is_length_equal(g.map) == 0)
    {
        free(g.map);
        return (ft_printf("Error\n"));
    }
    ft_printf("Map has equal lemgth\n");
    if (is_map_rounded_closed(g.map , g.map_h) == 0)
    {
        free(g.map);
        return (ft_printf("Error\n"));
    }
    ft_printf("Map is rounded by walls\n");
    if (valid_characters(&g) == 0)
    {
        free(g.map);
        return (ft_printf("Error\n"));
    }
    ft_printf("Map has just valid characters\n");
    ///////////////////////////////////// exit point
    find_exit_point(&g);
    ////////////////////////////////////playre_position
    find_player_position(&g);
    find_enemy_position(&g);
    ////////////////////////////////////////////////////
    if (valid_route(&g) == 0)
    {
        free(g.map);
        return (ft_printf("Error\n"));
    }
    ft_printf("All collections and exit point are reachable\n");
    ////////////////////////////////////////////////
    g.win = mlx_new_window(g.mlx, width * TILE, height * TILE, "so_long map test");
    if (!g.win) return (free(g.map), 1);
    ///////////////////////////////////// attaching characters
    g.map[g.player_y * (g.map_w + 1) + g.player_x] = '0'; //omiting player from map
    g.player_frames[0] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[1] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player_1.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[2] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player_2.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[3] = mlx_xpm_file_to_image(g.mlx,"texture and figure/player_3.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.wall = mlx_xpm_file_to_image(g.mlx, "texture and figure/wall.xpm", &w, &h);
    g.green_wall = mlx_xpm_file_to_image(g.mlx,"texture and figure/green_wall.xpm", &w, &h);
    g.collections = mlx_xpm_file_to_image(g.mlx,"texture and figure/collections.xpm", &w, &h);
    g.floor = mlx_xpm_file_to_image(g.mlx, "texture and figure/floor.xpm", &w, &h);
    g.floor_exit = mlx_xpm_file_to_image(g.mlx, "texture and figure/exit_floor.xpm", &w, &h);
    g.enemy = mlx_xpm_file_to_image(g.mlx, "texture and figure/enemy.xpm", &w, &h);
    g.winer = mlx_xpm_file_to_image(g.mlx,"texture and figure/win.xpm",&w_win, &h_win);
    g.loser = mlx_xpm_file_to_image(g.mlx, "texture and figure/lose.xpm",&w_lose, &h_lose);
    if (!g.wall || !g.green_wall || !g.floor || !g.player_frames[0] ||
        !g.player_frames[1] || !g.player_frames[2] || !g.player_frames[3] ||
        !g.collections || !g.floor_exit || !g.enemy || !g.winer || !g.loser)
        return (free(g.map), 1);
    /////////////////////////////////////// hooks and events    
    mlx_loop_hook(g.mlx, loop_master, &g);
    mlx_key_hook(g.win, handle_key, &g);
    mlx_hook(g.win, 17, 0, handle_close, &g);
    mlx_loop(g.mlx);
    free(g.map);
    free(g.moves_str);
    return 0;
}

