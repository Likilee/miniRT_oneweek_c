#ifndef PRINT_H
# define PRINT_H

# include "stdio.h"
# include "structures.h"
# include "mlx.h"
# include "utils.h"

void	write_color(t_color3 pixel_color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_rgb(t_color3 *color);

#endif
