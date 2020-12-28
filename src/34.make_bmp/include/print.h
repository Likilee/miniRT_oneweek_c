#ifndef PRINT_H
# define PRINT_H

# include "stdio.h"
# include "structures.h"
# include "mlx.h"
# include "utils.h"
# include "bitmap.h"

void	write_color(t_color3 pixel_color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_rgb(t_color3 *color);
int		get_r(int rgb);
int		get_g(int rgb);
int		get_b(int rgb);


/*
** src/print/save.c
*/
t_bmph	bmp_get_header(t_scene *scene);
void	bmp_save(t_scene *scene);

#endif
