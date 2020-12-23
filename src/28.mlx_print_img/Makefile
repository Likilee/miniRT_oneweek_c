NAME = minirt
CC = gcc
RM = rm -rf
CFLAG =  -g3 -fsanitize=address # -Wall -Wextra -Werror
MAKE = make
MLX = libmlx.dylib
MLX_DIR = ./mlx
MLXFLAG = -L./mlx -lmlx -framework OpenGL -framework AppKit
INCLUDE = -I./include -I./mlx
all : $(NAME)

clean :
	$(MAKE) -C $(MLX_DIR) clean;
fclean : clean
	$(RM) $(NAME)
re : fclean all

run : all
	./$(NAME)
ppm : all
	./$(NAME) > result.ppm
open : ppm
	open ./result.ppm
$(NAME) : $(MLX_DIR)/$(MLX)
	$(CC) $(CFLAG) $(MLXFLAG) ./src/*.c ./src/*/*.c ./src/*/*/*.c $(INCLUDE) -o $(NAME)
	install_name_tool -change $(MLX) $(MLX_DIR)/$(MLX) $(NAME)
$(MLX_DIR)/$(MLX) :
	$(MAKE) -C $(MLX_DIR) all
.PHONY : all clean re ppm open run
