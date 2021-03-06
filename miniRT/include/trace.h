/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:00:02 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 17:02:51 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"
# include "print.h"
# include "scene.h"
# include <pthread.h>

/*
** trace/render
*/
void		render_preview(t_cntl *cntl);
void		render_path_trace(t_cntl *cntl);
void		render_phong(t_cntl *cntl);
void		pth_data_init(t_pth_data *data, t_cntl *cntl);

/*
** trace/hit
*/
t_bool		hit(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_obj(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_sphere(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_pl_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_plane(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_sq_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_square(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_cy_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_cylinder(t_objects *obj, t_ray *ray, t_hit_rec *rec);
double		hit_finite_cylinder(t_cylinder *cy, t_ray *ray, t_hit_rec *rec);
double		hit_disk(t_cylinder *cy, t_ray *ray, t_hit_rec *rec, t_bool is_top);
void		record_disk(t_cylinder *cy, t_ray *ray, t_hit_rec *rec, double t);
void		record_cylinder(t_cylinder *cy, t_ray *ray,
							t_hit_rec *rec, double t);
double		cylinder_get_discriminant(t_cylinder *cy, t_ray r,
											double *half_b, double *a);
t_bool		cylinder_root_check(t_cylinder *cy, t_hit_rec *rec,
										double root, t_point3 p);
t_vec3		cylinder_normal(t_cylinder *cy, t_hit_rec *rec);
t_bool		hit_cy_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_vec3		world2object_cy(t_matrix44 *rotate, t_cylinder *cy, t_ray *ray);
t_bool		hit_triangle(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_cb_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_cube(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_pm_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec);
t_bool		hit_pyramid(t_objects *obj, t_ray *ray, t_hit_rec *rec);
void		set_face_normal(t_ray *r, t_hit_rec *rec);
void		get_record(t_hit_rec *rec, double root, t_objects *obj, t_ray *r);
void		object2world_rec(t_hit_rec *rec, t_vec3 *offset,
							t_matrix44 *r, t_matrix44 *r_n);

/*
** trace/ray
*/
t_point3	ray_at(t_ray *ray, double t);
t_ray		ray(t_point3 orig, t_vec3 dir);
t_color3	ray_color_preview(t_ray *r, t_scene *s, int light_on);
t_color3	ray_color_phong(t_ray *r, t_scene *s);
t_color3	ray_color_path_trace(t_ray *r, t_scene *s, int depth);
t_bool		in_shadow(t_objects *objs, t_ray light_ray, double light_len);
t_color3	direct_lighting(t_objects *objs, t_ray *r, t_hit_rec *rec);
t_color3	direct_lighting_get(t_objects *objs, t_light *light,
								t_ray *r, t_hit_rec *rec);
t_color3	direct_lighting_point(t_objects *objs, t_light *light,
								t_ray *r, t_hit_rec *rec);
t_color3	direct_lighting_parallel(t_objects *objs, t_light *light,
								t_ray *r, t_hit_rec *rec);
t_vec3		reflect(t_vec3 v, t_vec3 n);
t_vec3		refract(t_vec3 *uv, t_vec3 *n, double etai_over_etat);
t_bool		scatter(t_ray *r_in, t_hit_rec *rec,
					t_color3 *attenuation, t_ray *scattered);
t_bool		scatter_lambertian(t_hit_rec *rec,
								t_color3 *attenuation, t_ray *scattered);
t_bool		scatter_metal(t_ray *r_in, t_hit_rec *rec,
							t_color3 *attenuation, t_ray *scattered);
t_bool		scatter_dielectric(t_ray *r_in, t_hit_rec *rec,
							t_color3 *attenuation, t_ray *scattered);

/*
** trace/texture
*/
void		get_sphere_uv(t_hit_rec *rec);
void		get_disk_uv(t_hit_rec *rec, t_cylinder *cy);
void		get_cylinder_uv(t_hit_rec *rec, t_cylinder *cy);
void		get_square_uv(t_hit_rec *rec, t_square *sq);
t_color3	albedo(t_hit_rec *rec);
t_color3	albedo_checker(t_hit_rec *rec);
t_color3	albedo_checker_uv(t_hit_rec *rec);
t_color3	albedo_rainbow_normal(t_hit_rec *rec);
t_color3	albedo_image_uv(t_hit_rec *rec);
t_color3	albedo_skybox(t_hit_rec *rec);
t_color3	color_background(t_ray *r, t_scene *s, t_hit_rec *rec);
t_color3	albedo_wave(t_hit_rec *rec);

#endif
