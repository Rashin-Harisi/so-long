#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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
        else if (g->map[i] == 'P')
            mlx_put_image_to_window(g->mlx, g->win, g->player_frames[g->current_frame], x * TILE, y * TILE);

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

int main(void)
{
    t_game g;
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
    mlx_loop_hook(g.mlx, animate_player, &g);
    if (!g.wall || !g.green_wall || !g.floor || !g.player_frames[0] ||
        !g.player_frames[1] || !g.player_frames[2] || !g.player_frames[3])
        return (free(g.map), 1);

    draw_map(&g);

    mlx_loop(g.mlx);
    free(g.map);
    return 0;
}

