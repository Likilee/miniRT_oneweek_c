.SUFFIXEX : .c .o
NAME = minirt
CC = gcc
RM = rm -rf
CFLAG = -O3 -g3 -fsanitize=address -Wall -Wextra -Werror
MAKE = make
MLX = libmlx.dylib
MLX_DIR = ./lib/mlx
LIBFT = libft.a
LIBFT_DIR = ./lib/libft
LIB_FLAG = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L $(LIBFT_DIR) -lft
INCLUDE = -I./include -I./include/lib
SRC_CNTL_NAME = control.c \
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
			control_render.c
SRC_CNTL = $(addprefix src/control/, $(SRC_CNTL_NAME))
SRC_PARSE_NAME = read_rt.c \
			read_rt2.c \
			read_rt3.c \
			read_rt4.c \
			read_rt5.c \
			error_rt.c \
			error_rt2.c \
			error_rt3.c
SRC_PARSE = $(addprefix src/parse/, $(SRC_PARSE_NAME))
SRC_PRINT_NAME = color.c \
			filter.c \
			image.c
SRC_PRINT = $(addprefix src/print/, $(SRC_PRINT_NAME))
SRC_SCENE_NAME = camera.c \
			canvas.c \
			scene.c \
			object_create.c \
			object_create2.c \
			object_create3.c \
			object_free.c \
			object_utils.c
SRC_SCENE = $(addprefix src/scene/, $(SRC_SCENE_NAME))
SRC_HIT_NAME = hit.c \
			hit_sphere.c \
			hit_plane.c \
			hit_square.c \
			hit_cylinder.c \
			hit_cylinder2.c \
			hit_triangle.c \
			hit_cube.c \
			hit_pyramid.c \
			normal.c
SRC_HIT = $(addprefix src/trace/hit/, $(SRC_HIT_NAME))
SRC_RAY_NAME = ray.c \
			direct_lighting.c \
			direct_lighting_point.c \
			direct_lighting_parellel.c \
			indirect_lighting.c \
			reflect.c \
			refract.c \
			shadow.c
SRC_RAY = $(addprefix src/trace/ray/, $(SRC_RAY_NAME))
SRC_RENDER_NAME = render_preview.c \
			render_path_trace.c \
			render_phong.c
SRC_RENDER = $(addprefix src/trace/render/, $(SRC_RENDER_NAME))
SRC_TEXTURE_NAME = albedo.c \
				albedo2.c \
				get_uv.c \
				skybox.c
SRC_TEXTURE = $(addprefix src/trace/texture/, $(SRC_TEXTURE_NAME))
SRC_UTIL_NAME = common_utils.c \
			common_utils2.c \
			common_utils3.c \
			vec3_utils.c \
			vec3_utils2.c \
			vec3_utils3.c \
			vec3_utils4.c \
			matrix44_utils.c \
			matrix44_utils2.c \
			matrix44_utils3.c
SRC_UTIL = $(addprefix src/utils/, $(SRC_UTIL_NAME))
SRC_MAIN = src/main.c
SRC = $(SRC_MAIN) $(SRC_HIT) $(SRC_PARSE) $(SRC_UTIL) $(SRC_CNTL) $(SRC_PRINT) $(SRC_RAY) $(SRC_RENDER) $(SRC_SCENE) $(SRC_TEXTURE)
OBJ = $(SRC:.c=.o)
OBJDIR = ./obj
all : $(NAME)

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean;
	@$(RM) $(OBJ)
fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean;
	@$(MAKE) -C $(MLX_DIR) clean;
	@$(RM) $(NAME)
re : fclean all

run : all
	./$(NAME) ./rt/scene.rt
bonus : all

$(NAME) : $(OBJ) $(MLX_DIR)/$(MLX) $(LIBFT_DIR)/$(LIBFT)
	@$(CC) $(CFLAG) $(LIB_FLAG) $(OBJ) $(INCLUDE) -o $@
	@install_name_tool -change $(MLX) $(MLX_DIR)/$(MLX) $(NAME)
%.o : %.c
	@$(CC) $(CFLAG) -c $? -o $@ $(INCLUDE)
$(MLX_DIR)/$(MLX) :
	@$(MAKE) -C $(MLX_DIR) all
$(LIBFT_DIR)/$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR) all
.PHONY : all clean re ppm open run
