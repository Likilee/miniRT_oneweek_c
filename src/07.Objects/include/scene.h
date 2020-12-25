#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_canvas	canvas(int	width, int height);
t_camera	camera(t_canvas *canvas, t_point3 orig, double view_h, double focal_len);
t_sphere	*sphere(t_point3 center, double radius);
// objects utililty function
t_objects	*object(t_objects_type type, void *element);
void		oadd(t_objects **lst, t_objects *new);
int			osize(t_objects **lst);
void		odelone(t_objects *obj);
void		oclear(t_objects **lst);



#endif
