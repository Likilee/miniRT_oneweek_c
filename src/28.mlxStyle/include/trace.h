#ifndef RAY_H
# define RAY_H

# include "structures.h"
# include "utils.h"
# include "print.h"

/*
** trace/render
*/
t_data	render(t_scene *scene);

/*
** trace/hit
*/
t_bool		hit(t_objects *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_objects *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec);
t_bool		hit_plane(t_plane *pl, t_ray *ray, t_hit_record *rec);
t_bool		hit_square(t_objects *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_cylinder(t_objects *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_triangle(t_triangle *tr, t_ray *ray, t_hit_record *rec);
t_bool		hit_cb(t_objects *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_pm(t_objects *obj, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);

/*
** trace/ray
*/
t_point3	ray_at(t_ray *ray, double t);
t_ray		ray(t_point3 orig, t_vec3 dir);
t_color3	ray_color(t_ray *r, t_objects *objs, t_global *global, int depth);
t_bool		in_shadow(t_objects *objs, t_ray light_ray, double light_len);
t_color3	direct_lighting(t_objects *objs, t_ray *r, t_hit_record *rec);
t_color3	direct_lighting_get(t_objects *objs, t_light *light, t_ray *r, t_hit_record *rec);
t_color3	direct_lighting_point(t_objects *objs, t_light *light, t_ray *r, t_hit_record *rec);
t_color3	direct_lighting_parallel(t_objects *objs, t_light *light, t_ray *r, t_hit_record *rec);
t_vec3		reflect(t_vec3 v, t_vec3 n);
t_vec3		refract(t_vec3 *uv, t_vec3 *n, double etai_over_etat);
t_bool		scatter(t_ray *r_in, t_hit_record *rec, t_color3 *attenuation, t_ray * scattered);
t_bool		scatter_lambertian(t_hit_record *rec, t_color3 *attenuation, t_ray * scattered);
t_bool		scatter_metal(t_ray *r_in, t_hit_record *rec, t_color3 *attenuation, t_ray * scattered);
t_bool		scatter_dielectric(t_ray *r_in, t_hit_record *rec, t_color3 *attenuation, t_ray * scattered);

/*
** trace/texture
*/
void		get_sphere_uv(t_hit_record *rec);
void		get_cylinder_uv(t_hit_record *rec, t_cylinder *cy);
t_color3	albedo(t_hit_record *rec);
t_color3	albedo_checker(t_hit_record *rec);
t_color3	albedo_checker_uv(t_hit_record *rec);
t_color3	albedo_rainbow_normal(t_hit_record *rec);

#endif
