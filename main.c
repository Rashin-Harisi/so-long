#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define TILE 32
#define PLAYER_FRAMES 4

typedef struct s_game
{
    void *mlx;
    void *win;
    char *map;
    int map_w;
    int map_h;
    void *wall;
    void *green_wall;
    void *floor;
    void *player_frames[PLAYER_FRAMES];
    int current_frame;
    int player_x;
    int player_y;
    int moves;
} t_game;

static int  slen(const char *s)
{
    int i = 0;
    while (s && s[i]) i++;
    return i;
}

static char *read_all(int fd)
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

static void draw_map(t_game *g)
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
        mlx_put_image_to_window(g->mlx, g->win, g->player_frames[g->current_frame], g->player_x * TILE, g->player_y * TILE);

        x++;
    }
}

int animate_player (void *param)
{
    t_game *game = (t_game *)param;
    static int counter = 0;
    counter ++;
    if (counter % 50 == 0)
    {
        game->current_frame = (game->current_frame + 1) % PLAYER_FRAMES;
        draw_map(game);
    }
    return 0;
}

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
    else if (keycode == 65362) //UP
        new_y--;
    else if (keycode == 65364) //DOWN
        new_y++;
    else if (keycode == 65361) //LEFT
        new_x--;
    else if (keycode == 65363) //RIGHT
        new_x++;

    if (new_x == g->player_x && new_y == g->player_y) //no movement
        return (0);
    if (g->map[new_y * (g->map_w + 1) + new_x] == '1') //wall encounter
        return (0);
    
    g->player_x = new_x;
    g->player_y = new_y;
    g->moves++;
    draw_map(g);
    return (0);
}

int handle_close(void *params)
{
    t_game *g = (t_game *) params;
    mlx_destroy_window(g->mlx , g->win);
    free(g->map);
    exit(0);
    return(0);
}
void find_player_position(t_game *params)
{
    t_game *g = (t_game *)params;
    int x = 0;
    int y = 0;
    
    for( int i=0 ; g->map[i] ; i++)
    {
        if (g->map[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        if (g->map[i] == 'P')
        {
            g->player_x = x;
            g->player_y = y;
            return;
        }
        x++;
    }
}

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
    g.player_frames[0] = mlx_xpm_file_to_image(g.mlx,"player.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[1] = mlx_xpm_file_to_image(g.mlx,"player_1.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[2] = mlx_xpm_file_to_image(g.mlx,"player_2.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.player_frames[3] = mlx_xpm_file_to_image(g.mlx,"player_3.xpm", &w, &h);
    if (w != TILE || h != TILE) return (free(g.map), 1);
    g.current_frame = 0;

    
    g.wall = mlx_xpm_file_to_image(g.mlx, "wall.xpm", &w, &h);
    g.green_wall = mlx_xpm_file_to_image(g.mlx,"green_wall.xpm", &w, &h);
    g.floor = mlx_xpm_file_to_image(g.mlx, "floor.xpm", &w, &h);
    if (!g.wall || !g.green_wall || !g.floor || !g.player_frames[0] ||
        !g.player_frames[1] || !g.player_frames[2] || !g.player_frames[3])
        return (free(g.map), 1);
        
    mlx_loop_hook(g.mlx, animate_player, &g);
    mlx_key_hook(g.win, handle_key, &g);
    mlx_hook(g.win, 17, 0, handle_close, &g);

    draw_map(&g);
    mlx_loop(g.mlx);
    free(g.map);
    printf("moves : %d\n", g.moves);
    return 0;
}

