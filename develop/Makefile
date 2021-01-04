NAME = minirt
CC = gcc
RM = rm -rf
CFLAG =  -O3 -g3 -fsanitize=address -Wall -Wextra -Werror
MAKE = make
MLX = libmlx.dylib
MLX_DIR = ./lib/mlx
LIBFT = libft.a
LIBFT_DIR = ./lib/libft
LIB_FLAG = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L $(LIBFT_DIR) -lft
INCLUDE = -I./include -I./include/lib
SRC_CNTL = control.c \
			control_save.c \
			control_save2.c \
			control_object.c \
			control_object2.c \
			control_object_scale.c \
			control_object_translate.c \
			control_object_translate2.c \
			control_light.c \
			control_light2.c \
			control_camera.c \
			control_camera2.c \
			control_console_msg.c \
			control_console_msg2.c \
			control_default.c \
			control_init.c \
			control_save.c \
			control_save2.c \
			control_render.c
SRC_PARSE = read_rt.c \
			read_rt2.c \
			read_rt3.c \
			read_rt4.c \
			read_rt5.c \
			error_rt.c \
			error_rt2.c \
			error_rt3.c
SRC_PRINT = color.c \
			filter.c \
			image.c
SRC_SCENE = camera.c \
			canvas.c \
			scene.c \
			object_create.c \
			object_create2.c \
			object_create3.c \
			object_free.c \
			object_utils.c
SRC_HIT = hit.c \
			hit_sphere.c \
			hit_plane.c \
			hit_square.c \
			hit_cylinder.c \
			hit_cylinder2.c \
			hit_triangle.c \
			hit_cube.c \
			hit_pyramid.c \
			normal.c


all : $(NAME)

clean :
	# $(MAKE) -C $(MLX_DIR) clean;
	# $(MAKE) -C $(LIBFT_DIR) clean;
fclean : clean
	# $(MAKE) -C $(LIBFT_DIR) fclean;
	$(RM) $(NAME)
re : fclean all

run : re
	./$(NAME) ./rt/scene.rt
bonus : all

$(NAME) : $(MLX_DIR)/$(MLX) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(CFLAG) $(LIB_FLAG) ./src/*.c ./src/*/*.c ./src/*/*/*.c $(INCLUDE) -o $(NAME)
	install_name_tool -change $(MLX) $(MLX_DIR)/$(MLX) $(NAME)
$(MLX_DIR)/$(MLX) :
	$(MAKE) -C $(MLX_DIR) all
$(LIBFT_DIR)/$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR) all
.PHONY : all clean re ppm open run
