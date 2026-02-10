#ifndef SO_LONG
# define SO_LONG

# include "mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"


# define TILE 32
# define PLAYER_FRAMES 4

typedef struct s_game
{
    void *mlx;
    void *win;
    char *map;
    int map_w;
    int map_h;
    void *wall;
    void *green_wall;
    void *floor;
    void *floor_exit;
    void *collections;
    void *player_frames[PLAYER_FRAMES];
    int current_frame;
    int player_x;
    int player_y;
    int moves;
    int exit_x;
    int exit_y;
    int collectibles;
} t_game;

void draw_map(t_game *g);
int handle_key(int keycode, void *params);
void find_player_position(t_game *g);
int animate_player (void *param);
char *read_all(int fd);
int handle_close(void *params);
void find_exit_point(t_game *g);
void free_array(char **lines);
int fail_handel(char **lines);
int is_length_equal(char *map);
int is_map_rounded_closed(char *map, int map_h);
int valid_characters(t_game *g);



#endif