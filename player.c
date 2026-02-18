#include "so_long.h"

int animate_player (void *param)
{
    t_game *game = (t_game *)param;
    if (ft_strncmp(game->state, "RUNING", ft_strlen("RUNING")) != 0)
        return (0);
    static int counter = 0;
    counter ++;
    if (counter % 50 == 0)
    {
        game->current_frame = (game->current_frame + 1) % PLAYER_FRAMES;
        game->needs_redraw = 1;
        //draw_map(game);
    }
    return 0;
}

void find_player_position(t_game *g)
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
        if (g->map[i] == 'P')
        {
            g->player_x = x;
            g->player_y = y;
            return;
        }
        x++;
    }
}