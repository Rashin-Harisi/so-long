#include "so_long.h"

void find_enemy_position(t_game *g)
{
    int x = 0;
    int y = 0;

    for (int i = 0; g->map[i]; i++)
    {
        if (g->map[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        if (g->map[i] == 'X')
        {
            g->enemy_x = x;
            g->enemy_y = y;
            return;
        }
        x++;
    }
}

long time_now(void)
{
    struct timeval tv;
    long now = 0;
    gettimeofday(&tv, NULL);
    now = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
    return (now);
}

int check_neghbors_enemy(t_game *params, int x, int y)
{
    int index;
    if (!params || !params->map)
        return (0);
    if (x < 0 || x >= params->map_w ||
        y < 0 || y >= params->map_h)
        return (0);
    index = y * (params->map_w + 1) + x;
    if (params->map[index] == '1' || params->map[index] == '\n' ||
        params->map[index] == '\0')
        return (0);
    return (1);
}

void update_enemy_location(t_game *params, t_neighbor n[], int count)
{
    int i = 0;
    int new_x = params->enemy_x;
    int new_y = params->enemy_y;
    int min = INT_MAX;
    if (count == 0)
    {
        params->enemy_x = params->prev_enemy_x;
        params->enemy_y = params->prev_enemy_y;
        return;
    }
    while (i < count)
    {
        if ((abs(n[i].x - params->player_x) + abs(n[i].y - params->player_y)) < min)
        {
            min = (abs(n[i].x - params->player_x) + abs(n[i].y - params->player_y));
            new_x = n[i].x;
            new_y = n[i].y;
        }
        i++;
    }
    params->enemy_x = new_x;
    params->enemy_y = new_y;
}

int game_over(t_game *params)
{
    if (params->enemy_x == params->player_x &&
        params->enemy_y == params->player_y)
        return (1);
    return (0);
}

int game_loop(t_game *params)
{
    t_neighbor n[4];
    int count = 0;
    int num = rand() % 100;
    int old_x = params->enemy_x;
    int old_y = params->enemy_y;
    long now = time_now();
    if (ft_strncmp(params->state, "RUNING", ft_strlen("RUNING")) != 0)
        return (0);
    if (now - params->last_enemy_ms < 500)
        return (0);
    if (check_neghbors_enemy(params, params->enemy_x + 1, params->enemy_y) &&
        !(params->prev_enemy_x == params->enemy_x + 1 && params->prev_enemy_y == params->enemy_y))
    {
        n[count].x = params->enemy_x + 1;
        n[count].y = params->enemy_y;
        count++;
    }
    if (check_neghbors_enemy(params, params->enemy_x - 1, params->enemy_y) &&
        !(params->prev_enemy_x == params->enemy_x - 1 && params->prev_enemy_y == params->enemy_y))
    {
        n[count].x = params->enemy_x - 1;
        n[count].y = params->enemy_y;
        count++;
    }
    if (check_neghbors_enemy(params, params->enemy_x, params->enemy_y + 1) &&
        !(params->prev_enemy_x == params->enemy_x && params->prev_enemy_y == params->enemy_y + 1))
    {
        n[count].x = params->enemy_x;
        n[count].y = params->enemy_y + 1;
        count++;
    }
    if (check_neghbors_enemy(params, params->enemy_x, params->enemy_y - 1) &&
        !(params->prev_enemy_x == params->enemy_x && params->prev_enemy_y == params->enemy_y - 1))
    {
        n[count].x = params->enemy_x;
        n[count].y = params->enemy_y - 1;
        count++;
    }
    if (count > 0)
    {
        if (num < 70)
            update_enemy_location(params, n, count);
        else
        {
            int index = rand() % count;
            params->enemy_x = n[index].x;
            params->enemy_y = n[index].y;
        }
    }
    params->prev_enemy_x = old_x;
    params->prev_enemy_y = old_y;
    if (game_over(params))
    {
        params->state = "LOSE";
        params->end_time = time_now();
        if (!params->last_win)
            params->last_win = mlx_new_window(params->mlx, 300, 300 , "end");
        return (0);
    }
    params->last_enemy_ms = now;
    // printf("enemy %d %d\n", params->enemy_x, params->enemy_y);
    return (0);
}