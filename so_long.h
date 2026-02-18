#ifndef SO_LONG
#define SO_LONG

#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include <sys/time.h>
# include <limits.h>
# include <math.h>
# include <time.h>

#define TILE 32
#define PLAYER_FRAMES 4

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
    char *moves_str;
    int exit_x;
    int exit_y;
    int collectibles;
    int reach_c;
    int reach_e;
    void *enemy;
    int enemy_x;
    int enemy_y;
    long last_enemy_ms;
    int prev_enemy_x;
    int prev_enemy_y;
    char *state;
    long end_time;
    void *winer;
    void *loser;
    void *last_win;
} t_game;

typedef struct s_queue
{
    int *x;
    int *y;
    int head;
    int tail;
    int size;
} t_queue;

typedef struct s_neighbor
{
    int x;
    int y;
} t_neighbor;

void draw_map(t_game *g);
int handle_key(int keycode, void *params);
void find_player_position(t_game *g);
int animate_player(void *param);
char *read_all(int fd);
int handle_close(void *params);
void find_exit_point(t_game *g);
void free_array(char **lines);
int fail_handel(char **lines);
int is_length_equal(char *map);
int is_map_rounded_closed(char *map, int map_h);
int valid_characters(t_game *g);
t_queue *queue_create(int max_size);
int queue_push(t_queue *q, int x, int y);
int queue_pop(t_queue *q, int *x, int *y);
void queue_free(t_queue *q);
int visit_tile(char *map, t_game *params, int x, int y);
int check_neghbors(t_game *params, char *map, int x, int y);
int valid_route(t_game *params);
void movies_string(t_game *params);
void find_enemy_position(t_game *g);
int game_loop(t_game *params);
int game_over(t_game *params);
int check_neghbors_enemy(t_game *params, int x, int y);
long time_now(void);
int loop_master(void *params);
void update_enemy_location(t_game *params, t_neighbor n[], int count);
void draw_last_window(void *params);

#endif