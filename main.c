#include "so_long.h"

static int draw_images(t_game *g,int *w, int *h)
{
    int w_lose;
    int w_win;
    int h_lose;
    int h_win;

    g->map[g->player_y * (g->map_w + 1) + g->player_x] = '0'; 
    if (!draw_player(g, w, h))
        return (0);
    g->wall = mlx_xpm_file_to_image(g->mlx, "texture/wall.xpm", w, h);
    g->green_wall = mlx_xpm_file_to_image(g->mlx,"texture/green_wall.xpm", w, h);
    g->collections = mlx_xpm_file_to_image(g->mlx,"texture/collections.xpm", w, h);
    g->floor = mlx_xpm_file_to_image(g->mlx, "texture/floor.xpm", w, h);
    g->floor_exit = mlx_xpm_file_to_image(g->mlx, "texture/exit_floor.xpm", w, h);
    g->enemy = mlx_xpm_file_to_image(g->mlx, "texture/enemy.xpm", w, h);
    g->winer = mlx_xpm_file_to_image(g->mlx,"texture/win.xpm", &w_win, &h_win);
    g->loser = mlx_xpm_file_to_image(g->mlx, "texture/lose.xpm", &w_lose, &h_lose);
    if (!g->wall || !g->green_wall || !g->floor || !g->player_frames[0] ||
        !g->player_frames[1] || !g->player_frames[2] || !g->player_frames[3] ||
        !g->collections || !g->floor_exit || !g->enemy || !g->winer || !g->loser)
        return (0);
    return (1);
}

static int initial_setup(t_game *g)
{
    ft_bzero(g, sizeof(t_game));
    g->moves_str = NULL;
    g->state = "RUNING";
    movies_string(g);
    g->mlx = mlx_init();
    if (!g->mlx) 
        return (0);
    srand(time(NULL));
    return (1);
}

static int reading_map(t_game *g)
{
    int fd;
    int width;
    int height;
    int i;

    i = -1;
    width = 0;
    height = 0;
    fd = open("map.ber", O_RDONLY);
    if (fd < 0) 
        return (0);
    g->map = read_all(fd);
    close(fd);
    if (!g->map) 
        return (0);
    while (g->map[width] && g->map[width] != '\n') 
        width++;
    while (g->map[++i])
    {
        if (g->map[i] == '\n') 
            height++;
    }
    height += 1;
    g->map_w = width;
    g->map_h = height;
    return (1);
}

int map_validation(t_game *g)
{
    if(is_length_equal(g->map) == 0)
        return (fail_validation(g));
    if (is_map_rounded_closed(g->map , g->map_h) == 0)
        return (fail_validation(g));
    if (valid_characters(g) == 0)
        return (fail_validation(g));
    find_exit_point(g);
    find_player_position(g);
    find_enemy_position(g);
    if (valid_route(g) == 0)
        return (fail_validation(g));
    return (1);
}

int main(void)
{
    int w;
    int h;
    t_game g;

    if (!initial_setup(&g))
        return (1);
    if (!reading_map(&g))
        return (1);
    if (!map_validation(&g))
        return (1);
    g.win = mlx_new_window(g.mlx, g.map_w * TILE, g.map_h * TILE, "so_long map test");
    if (!g.win) 
        return (free(g.map), 1);
    if (!draw_images(&g, &w, &h))
    {
        free(g.map);
        free(g.moves_str);
        return (1);
    }
    mlx_loop_hook(g.mlx, loop_master, &g);
    mlx_key_hook(g.win, handle_key, &g);
    mlx_hook(g.win, 17, 0, handle_close, &g);
    mlx_loop(g.mlx);
    free(g.map);
    free(g.moves_str);
    return 0;
}

