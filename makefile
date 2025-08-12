# **************************************************************************** #
#                               cub3D Makefile                                 #
# **************************************************************************** #

NAME        = cub3D

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g

# Directories
SRC_DIR     = src
OBJ_DIR     = objects
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# Sources
SRC_FILES   = main.c \
			  parsing/file_validation.c \
			  parsing/read_map.c \
			  parsing/map_validation.c\
			  parsing/xy_position.c\
			  parsing/utils_0.c\
			  parsing/utils_1.c\
			  parsing/utils_2.c\
			  parsing/test.c\
			  getnextline/get_next_line.c \
			  getnextline/get_next_line_utils.c\
			  init/init_all.c init/mlx_hook.c init/player_mov.c\
			  utils.c\
			  raycasting/raycasting.c

SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Includes
INCLUDES    = -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

# Compile and link
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -lm -lXext -lX11 -o $(NAME)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re