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