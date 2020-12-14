#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "math_utils.h"

t_canvas	canvas(int	width, int height);
t_camera	camera(t_canvas *canvas, t_point3 orig, double view_h, double focal_len);
t_sphere	*sphere(t_point3 center, double radius, t_material *mat);
// objects utililty function
t_objects	*object(t_objects_type type, void *element, t_matrix44 *trans);
void		oadd(t_objects **lst, t_objects *new);
int			osize(t_objects **lst);
void		odelone(t_objects *obj);
void		oclear(t_objects **lst);
t_light		*light(t_point3 light_origin, t_color3 light_color, double ka);
t_plane		*plane(t_point3 p, t_vec3 normal, t_material *mat);
t_square	*square(t_point3 p, t_vec3 normal, double side_len, t_material *mat);
t_cylinder	*cylinder(t_point3 center_bottom, t_vec3 axis, double diameter, double height, t_material *mat);
t_triangle	*triangle(t_point3 p0, t_point3 p1, t_point3 p2, t_material *mat);
t_material	*material(t_material_type type, t_color3 albedo, double option1);

#endif
