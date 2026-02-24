NAME        := so_long

# Headers (for dependency)
HEADER      := so_long.h

# -------- Sources --------
# put your mandatory .c files in root here
MANDATORY_SRC := main.c \
				draw_map.c \
				helper.c \
				key_event.c \
				player.c \
				exitpoint.c \
				map_validation.c \
				fool_fill.c \
				route_validation.c \
				enemy.c \
				enemy_helper.c \
				draw_last_window.c 

# put your bonus .c files inside bonus/ here (examples)


# If you have shared files, put them here:


MANDATORY_OBJ := $(MANDATORY_SRC:.c=.o)


# -------- Compiler --------
CC          := cc -g
CFLAGS      := -Wall -Wextra -Werror -Wno-incompatible-pointer-types

# -------- Libft --------
LIBFT_DIR   := libft
LIBFT_A     := $(LIBFT_DIR)/libft.a

# -------- MiniLibX (Linux) --------
MLX_DIR     := mlx_linux
MLX_A       := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Includes
INC         := -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(MANDATORY_OBJ) 
	$(CC) $(CFLAGS) $(MANDATORY_OBJ)  -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJ) 
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
