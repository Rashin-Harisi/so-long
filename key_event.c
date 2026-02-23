#include "so_long.h"

static int key_check(int keycode, int *new_x, int *new_y , t_game *g)
{
    if (keycode == 65307) //ESC keycode
    {
        handle_close(g);
        return (0);
    }
    else if (keycode == 119 || keycode == 65362) //UP
        (*new_y)--;
    else if (keycode == 115 || keycode == 65364) //DOWN
        (*new_y)++;
    else if (keycode == 97 || keycode == 65361) //LEFT
        (*new_x)--;
    else if (keycode == 100 || keycode == 65363) //RIGHT
        (*new_x)++;
    return (1);
}

static int win_situation(t_game *g)
{
    g->state = "WIN";
    g->end_time = time_now();
    if (!g->last_win)
        g->last_win = mlx_new_window(g->mlx, 300, 300 , "end");
    return (0);
}

static int lose_situation(t_game *g)
{
    g->state = "LOSE";
    g->end_time = time_now();
    if (!g->last_win)
        g->last_win = mlx_new_window(g->mlx, 300, 300 , "end");
    return (0);
}

static int check_movement(t_game *g, int *index , int new_x, int new_y)
{
    if (new_x == g->player_x && new_y == g->player_y) //no movement
        return (0);
    if (new_x < 0 || new_y < 0 || new_x >= g->map_w || new_y >= g->map_h)
        return (0);
    *index = new_y * (g->map_w + 1) + new_x;
    if (g->map[*index] == '1') //wall encounter
        return (0);
    if (g->map[*index] == 'C')
    {
        g->collectibles--;
        g->map[*index] = '0';
    }
    return (1);
}

int handle_key(int keycode, void *params)
{
    t_game *g;
    int new_x;
    int new_y;
    int index;

    g = (t_game *)params;
    new_x = g->player_x;
    new_y = g->player_y;
    index = 0;
    if (ft_strncmp(g->state,"RUNING",ft_strlen("RUNING")) != 0)
        return (0);
    if (!key_check(keycode, &new_x , &new_y, g))
        return (0);
    if (!check_movement(g, &index, new_x, new_y))
        return (0);
    if (new_x == g->exit_x && new_y == g->exit_y && g->collectibles == 0)
        return (win_situation(g));
    if (new_x == g->enemy_x && new_y == g->enemy_y)
        return (lose_situation(g));
    g->player_x = new_x;
    g->player_y = new_y;
    g->moves++;
    movies_string(g);
    printf("moves : %d\n", g->moves);
    g->needs_redraw = 1;
    return (0);
}
