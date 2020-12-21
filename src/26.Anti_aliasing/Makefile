NAME = minirt

all :
	gcc -g3 -fsanitize=address ./src/*.c ./src/*/*.c  ./src/*/*/*.c -o $(NAME) -I./include
clean :
	rm -rf $(NAME)
re : clean all

run : all
	./$(NAME)
ppm : all
	./$(NAME) > result.ppm
open : ppm
	open ./result.ppm
.PHONY : all clean re ppm open run
