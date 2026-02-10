#include "so_long.h"

void find_exit_point(t_game *g)
{
    int i;
    int x = 0;
    int y = 0;

    i = 0;
    for( int i=0 ; g->map[i] ; i++)
    {
        if (g->map[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        if (g->map[i] == 'E')
        {
            g->exit_x = x;
            g->exit_y = y;
            return;
        }
        x++;
    }
}