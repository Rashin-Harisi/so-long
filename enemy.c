#include "so_long.h"

void find_enemy_position(t_game *g)
{
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
    struct  timeval tv;
    long now = 0;
    gettimeofday(&tv,NULL);
    now = tv.tv_sec * 1000L + tv.tv_usec/1000L;
    return (now);
}

int check_neghbors_enemy(t_game *params,int x, int y)
{
    int index;
    if (!params || !params->map)
        return (0);
    if (x < 0 || x >= params->map_w ||
        y < 0 || y >= params->map_h)
        return (0);
    index = y * (params->map_w + 1) + x;
    if (params->map [index] == '1' || params->map [index] == '\n' ||
        params->map [index] == '\0' || params->map[index] == 'C')
            return (0);
    return (1);
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
    long now = time_now();
    if (now - params->last_enemy_ms < 1000)
        return (0);
    if (check_neghbors_enemy(params, params->enemy_x + 1, params->enemy_y))
        params->enemy_x++;
    else if (check_neghbors_enemy(params, params->enemy_x - 1, params->enemy_y))
        params->enemy_x--;
    else if (check_neghbors_enemy(params, params->enemy_x , params->enemy_y + 1))
        params->enemy_y++;
    else if (check_neghbors_enemy(params, params->enemy_x, params->enemy_y - 1))
        params->enemy_y--;
    draw_map(params);
    if (game_over(params))
    {
        //lose_animation(params);
        handle_close(params);
    }
    params->last_enemy_ms = now;
    //printf("enemy %d %d\n", params->enemy_x, params->enemy_y);
    return (0);
}