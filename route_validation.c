#include "so_long.h"

t_queue *queue_create(int max_size)
{
    t_queue *q;
    q = malloc(sizeof(t_queue));
    if (!q)
        return (NULL);
    q->x = malloc(sizeof(int) * max_size);
    q->y = malloc(sizeof(int) * max_size);
    if (!q->x || !q->y)
    {
        free(q->x);
        free(q->y);
        free(q);
        return (NULL);
    }
    q->head = 0;
    q->tail = 0;
    q->size = max_size;
    return (q);
}

int queue_push(t_queue *q, int x, int y)
{
    if (q->tail >= q->size)
        return (0); //full
    q->x[q->tail] = x;
    q->y[q->tail] = y;
    q->tail++;
    return (1);
}

int queue_pop(t_queue *q, int *x, int *y)
{
    if (q->head == q->tail)
        return (0);//empty
    *x = q->x[q->head];
    *y = q->y[q->head];
    q->head++;
    return (1);
}

void queue_free(t_queue *q)
{
    if (!q)
        return ;
    free(q->x);
    free(q->y);
    free(q);
}

void check_tile(char *map, t_game *params, int x, int y)
{
    int index[5];//index_curr;index_up;index_down;index_left;index_rigth
    int map_w = params->map_w;
    int map_h = params->map_h;

    if (!map || x < 0 || y < 0 || x >= map_w || y >= map_h)
        return ;
    index[0] = y * (map_w + 1) + x;
    index[1] = ((y - 1) * (map_w + 1)) + x; 
    index[2] = ((y + 1) * (map_w + 1)) + x;
    index[3] = y * (map_w + 1) + (x - 1);
    index[4] = y * (map_w + 1) + (x + 1);
    if (map[index[1]] != '1')
        map[index[0]] = 'V';
    if (map[index[2]] != '1')
        map[index[0]] = 'V';
    if (map[index[3]] != '1')
        map[index[0]] = 'V';
    if (map[index[4]] != '1')
        map[index[0]] = 'V';
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
    q = queue_create(params->map_w * params->map_h);
    queue_push(q, params->player_x, params->player_y);
    map = ft_strdup(params->map);
    if (!map)
        return (0);
    while(queue_pop(q,&x, &y))
    {
        check_tile(map, params ,x , y);
        if (map[y * (params->map_w + 1) + (x + 1)] == 'V')
            queue_push(q, x + 1, y);
        if (map[(y + 1) * (params->map_w + 1) + x] == 'V')
            queue_push(q, x, y + 1);
        if (map[y * (params->map_w + 1) + (x - 1)] == 'V')
            queue_push(q, x - 1, y);
        if (map[(y + 1) * (params->map_w + 1) + x] == 'V')
            queue_push(q, x, y - 1);
    }
    free(map);
    return (1);    
}