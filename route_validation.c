#include "so_long.h"

int visit_tile(char *map, t_game *params, int x, int y)
{
    int index;
    int map_w = params->map_w;
  
    if (!map )
        return (0);
    index = y * (map_w + 1) + x;
    if (map[index] == '1' || map[index] == 'V' ||
        map[index] == '\n' || map[index] == '\0')
        return (0);
    if(map[index] == 'C') 
        params->reach_c++;
    else if (map[index] == 'E')
        params->reach_e = 1;
    map[index] = 'V';
    return (1);
}

int check_neghbors(t_game *params, char *map, int x, int y)
{
    int index;
    if (!map)
        return (0);
    if (x < 0 || x >= params->map_w ||
        y < 0 || y >= params->map_h)
        return (0);
    index = y * (params->map_w + 1) + x;
    if (map [index] == '1' || map[index] == 'V' ||
        map [index] == '\n' || map[index] == '\0' || map[index] == 'Q')
            return (0);
    if (map[index] != 'C' && map[index] != 'E') 
        map[index] = 'Q';
    return (1);
}
//FIFO = FIRST IN FIRST OUT
int valid_route(t_game *params)
{
    char *map;
    t_queue *q;
    int x;
    int y;

    if (!params || !params->map)
        return (0);
    params->reach_c = 0;
    params->reach_e = 0;
    map = ft_strdup(params->map);
    if (!map)
        return (0);
    q = queue_create(params->map_w * params->map_h);
    if (!q)
    {
        free(map);
        return (0);
    }
    if (!queue_push(q, params->player_x, params->player_y))
    {
        queue_free(q);
        free(map);
        return (0);
    }
    while(queue_pop(q,&x, &y))
    {
        if (x < 0 || y < 0 || x >= params->map_w || y >= params->map_h)
            continue;
        if (!visit_tile(map, params ,x , y))
            continue ;
        if (check_neghbors(params, map, x + 1, y) && !queue_push(q, x + 1, y))
            return (queue_free(q), free(map), 0);
        if (check_neghbors(params, map, x, y + 1) && !queue_push(q, x, y + 1))
            return (queue_free(q), free(map), 0);
        if (check_neghbors(params, map, x - 1, y) && !queue_push(q, x - 1, y))
            return (queue_free(q), free(map), 0);
        if (check_neghbors(params, map, x, y - 1) && !queue_push(q, x, y - 1))
            return (queue_free(q), free(map), 0);
    }
    queue_free(q);
    free(map);
    if (params->reach_c != params->collectibles)
        return (0);
    if (params->reach_e == 0)
        return (0);
    return (1);    
}