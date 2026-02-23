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

int draw_player(t_game *g, int *w, int *h)
{
    g->player_frames[0] = mlx_xpm_file_to_image(g->mlx,"texture/player.xpm", w, h);
    if (!g->player_frames[0] || *w != TILE || *h != TILE) 
        return (0);
    g->player_frames[1] = mlx_xpm_file_to_image(g->mlx,"texture/player_1.xpm", w, h);
    if (!g->player_frames[1] || *w != TILE || *h != TILE) 
        return (0);
    g->player_frames[2] = mlx_xpm_file_to_image(g->mlx,"texture/player_2.xpm", w, h);
    if (!g->player_frames[2] || *w != TILE || *h != TILE) 
        return (0);
    g->player_frames[3] = mlx_xpm_file_to_image(g->mlx,"texture/player_3.xpm", w, h);
    if (!g->player_frames[3] || *w != TILE || *h != TILE) 
        return (0);
    return (1);
}