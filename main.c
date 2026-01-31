#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define TILE 32

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

static void draw_map(void *mlx, void *win, char *map, void *wall, void *floor, void *player)
{
    int x = 0;
    int y = 0;

    for (int i = 0; map[i]; i++)
    {
        if (map[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        mlx_put_image_to_window(mlx, win, floor, x * TILE, y * TILE);

        if (map[i] == '1')
            mlx_put_image_to_window(mlx, win, wall, x * TILE, y * TILE);
        else if (map[i] == 'P')
            mlx_put_image_to_window(mlx, win, player, x * TILE, y * TILE);

        x++;
    }
}

int main(void)
{
    void *mlx = mlx_init();
    if (!mlx) return 1;

    int fd = open("map.ber", O_RDONLY);
    if (fd < 0) return 1;

    char *map = read_all(fd);
    close(fd);
    if (!map) return 1;

    int width = 0;
    while (map[width] && map[width] != '\n') width++;

    int height = 0;
    for (int i = 0; map[i]; i++)
        if (map[i] == '\n') height++;
    height += 1;

    void *win = mlx_new_window(mlx, width * TILE, height * TILE, "so_long map test");
    if (!win) return (free(map), 1);

    int w, h;
    void *wall = mlx_xpm_file_to_image(mlx, "wall.xpm", &w, &h);
    void *floor = mlx_xpm_file_to_image(mlx, "floor.xpm", &w, &h);
    void *player = mlx_xpm_file_to_image(mlx, "player.xpm", &w, &h);

    if (!wall || !floor || !player)
        return (free(map), 1);

    draw_map(mlx, win, map, wall, floor, player);

    mlx_loop(mlx);
    free(map);
    return 0;
}

