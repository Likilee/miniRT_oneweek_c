#ifndef RAY_H
# define RAY_H

# include "structures.h"
# include "vec3_utils.h"

t_point3	ray_at(t_ray *ray, double t);
t_ray		ray(t_point3 orig, t_vec3 dir);
t_color3	ray_color(t_ray *r, t_sphere *sp);
t_bool		hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);

#endif
