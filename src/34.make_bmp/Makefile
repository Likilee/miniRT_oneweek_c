NAME = minirt
CC = gcc
RM = rm -rf
CFLAG =  -O2 -g3 -fsanitize=address # -Wall -Wextra -Werror
MAKE = make
MLX = libmlx.dylib
MLX_DIR = ./lib/mlx
LIBFT = libft.a
LIBFT_DIR = ./lib/libft
LIB_FLAG = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L $(LIBFT_DIR) -lft
INCLUDE = -I./include -I./include/lib

all : $(NAME)

clean :
	# $(MAKE) -C $(MLX_DIR) clean;
	# $(MAKE) -C $(LIBFT_DIR) clean;
fclean : clean
	# $(MAKE) -C $(LIBFT_DIR) fclean;
	$(RM) $(NAME)
re : fclean all

run : re
	./$(NAME) scene.rt
ppm : all
	./$(NAME) > result.ppm
open : ppm
	open ./result.ppm
$(NAME) : $(MLX_DIR)/$(MLX) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(CFLAG) $(LIB_FLAG) ./src/*.c ./src/*/*.c ./src/*/*/*.c $(INCLUDE) -o $(NAME)
	install_name_tool -change $(MLX) $(MLX_DIR)/$(MLX) $(NAME)
$(MLX_DIR)/$(MLX) :
	$(MAKE) -C $(MLX_DIR) all
$(LIBFT_DIR)/$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR) all
.PHONY : all clean re ppm open run
