NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
INCDIR = inc
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC = $(SRCDIR)/main.c \
	  $(SRCDIR)/helper.c

OBJ = $(SRC:.c=.o)
INC = -I$(INCDIR) -I$(LIBFTDIR) -I$(MLX_DIR)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLX): | mlx
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

mlx:
	@test -d $(MLX_DIR) || git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

.PHONY: all clean fclean re mlx
