#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "vec3_utils.h"

t_canvas	canvas(int	width, int height);
t_camera	camera(t_canvas *canvas, t_point3 orig, double view_h, double focal_len);
t_sphere	*sphere(t_point3 center, double radius, t_color3 color);
// objects utililty function
t_objects	*object(t_objects_type type, void *element);
void		oadd(t_objects **lst, t_objects *new);
int			osize(t_objects **lst);
void		odelone(t_objects *obj);
void		oclear(t_objects **lst);
t_light		*light(t_point3 light_origin, t_color3 light_color);
t_plane		*plane(t_point3 p, t_vec3 normal, t_color3 color);


#endif