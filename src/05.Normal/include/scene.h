#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "vec3_utils.h"

t_canvas	canvas(int	width, int height);
t_camera	camera(t_canvas *canvas, t_point3 orig, double view_h, double focal_len);
t_sphere	sphere(t_point3 center, double radius);

#endif
