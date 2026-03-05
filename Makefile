NAME        := so_long
BONUS_NAME	:= .bonus_state

HEADER      := so_long.h

COMMON_SRC := key_event.c \
				player.c \
				exitpoint.c \
				map_validation.c \
				fool_fill.c \
				route_validation.c \
				draw_last_window.c \
				utils.c

MANDATORY_SRC := main.c \
				helper.c \
				draw_map.c 

BONUS_SRC := bonus/main.c \
			bonus/draw_map.c \
			bonus/helper.c \
			bonus/enemy.c \
			bonus/enemy_helper.c 

COMMON_OBJ := $(COMMON_SRC:.c=.o)
MANDATORY_OBJ := $(MANDATORY_SRC:.c=.o)
BONUS_OBJ := $(BONUS_SRC:.c=.o)

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g -Wno-incompatible-pointer-types

# Libft
LIBFT_DIR := libft
LIBFT_A   := $(LIBFT_DIR)/libft.a

# System-installed MiniLibX (Linux)
#MLX_FLAGS := -lmlx -lXext -lX11 -lm

# -------- MiniLibX (Linux) --------
MLX_DIR     := mlx_linux
MLX_A       := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Includes
INC         := -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(MANDATORY_OBJ) $(COMMON_OBJ)
	@rm -f $(BONUS_NAME)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(COMMON_OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "Mandatory part is build."

#MINILIBX(LINUX)
$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

bonus : $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT_A) $(COMMON_OBJ) $(BONUS_OBJ)
	@rm -f $(NAME) $(MANDATORY_OBJ)
	$(CC) $(CFLAGS) $(COMMON_OBJ) $(BONUS_OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@touch $(BONUS_NAME)
	@echo "Bonus part is built"

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJ) $(BONUS_OBJ) $(COMMON_OBJ) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) 
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re