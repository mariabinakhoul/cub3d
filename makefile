.PHONY: all clean fclean re

# Program file name
NAME	= cub3D

# Compiler and compilation flags
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3
# CFLAGS += -fsanitize=address  # Uncomment for debugging

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Sources
SRC_PATH = ./src/
SRC		= 	main.c \
			parsing/check_map.c\
			parsing/read_map.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./includes/ \
				-I ./libft/ \
				-I ./minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Create object directories
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/parsing

# Compile .c → .o
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Link program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

# Build Libft
$(LIBFT):
	make -C $(LIBFT_PATH)

# Build MLX
$(MLX):
	make -C $(MLX_PATH)

# Clean object files
clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

# Remove program executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

# Clean + rebuild
re: fclean all
