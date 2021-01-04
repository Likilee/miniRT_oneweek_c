/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:45:55 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 17:09:05 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"
# include "parse.h"

/*
** src/scene/camera.c
*/
t_camera	*camera_init(t_point3 lookfrom, t_vec3 look_dir, double hfov);
void		camera_set(t_canvas *canvas, t_camera *cam);

/*
** src/scene/scene.c
*/
t_scene		*scene_init(void);

/*
** src/scene/canvas.c
*/
t_canvas	canvas(int	width, int height);

/*
** src/scene/object
*/
t_objects	*object(t_obj_type type, void *element,
					t_material *m, t_texture *t);
void		oadd(t_objects **lst, t_objects *new);
t_objects	*olast(t_objects *lst);
int			osize(t_objects **lst);
t_sphere	*sphere(t_point3 center, double radius);
t_light		*light_point(t_point3 light_origin, t_color3 light_color,
						double ka, double brightness);
t_light		*light_parallel(t_vec3 dir, t_color3 light_color,
						double ka, double brightness);
t_plane		*plane(t_point3 p, t_vec3 normal);
t_square	*square(t_point3 p, t_vec3 normal, double side_len);
t_cylinder	*cylinder(t_point3 center_bottom, t_vec3 axis,
						double diameter, double height);
t_triangle	*triangle(t_point3 p0, t_point3 p1, t_point3 p2);
t_cube		*cube(t_point3 center, double side_len);
t_pyramid	*pyramid(t_point3 center, t_point3 top, double side_len);
t_material	*material(t_material_type type, double option1);
t_texture	*texture(t_tex_type type, t_color3 albedo1,
						t_color3 albedo2, double option1);
t_texture	*texture_img(t_data *img);
void		free_cube(t_cube *cb);
void		free_pyramid(t_pyramid *pm);

#endif
