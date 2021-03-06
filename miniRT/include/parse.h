/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:40:35 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 16:40:36 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structures.h"
# include "utils.h"
# include "scene.h"
# include "mlx.h"

/*
** src/parse/read_rt*.c
*/
t_scene		*read_rt(char *filepath, void *mlx);
void		parse_rt(t_scene *scene, char *line, void *mlx);
t_bool		parse_rt_header(t_scene *scene, char *line, void *mlx);
t_bool		parse_rt_default(t_scene *scene, char *line);
t_bool		parse_rt_bonus(t_scene *scene, char *line, void *mlx);
t_vec3		to_vec3(char **s);
void		parse_free4(char **a, char **b, char **c, char **d);
void		get_material(t_scene *scene, char *line);
void		get_texture(t_scene *scene, char *line);
void		get_texture_img(t_scene *scene, char *line, void *mlx);
void		get_resolution(t_scene *scene, char *line);
void		get_ambient(t_scene *scene, char *line);
void		get_lux(t_scene *scene, char *line);
void		get_background(t_scene *scene, char *line, void *mlx);
void		get_camera(t_scene *scene, char *line);
void		get_point_light(t_scene *scene, char *line);
void		get_parallel_light(t_scene *scene, char *line);
void		get_sphere(t_scene *scene, char *line);
void		get_plane(t_scene *scene, char *line);
void		get_square(t_scene *scene, char *line);
void		get_cylinder(t_scene *scene, char *line);
void		get_triangle(t_scene *scene, char *line);
void		get_cube(t_scene *scene, char *line);
void		get_pyramid(t_scene *scene, char *line);

/*
** src/parse/error_rt*.c
*/
void		parse_error_identifier(char *line);
void		parse_error_data_count(char **data, int n, char *line);
void		parse_error_img_filepath(void *img, char *line);
void		parse_data_set_double(char **data, int n, char *line);
void		parse_data_set_zero_to_one(char **data, int n, char *line);
void		data_is_double(char *str, char *line);
void		data_is_integer(char *str, char *line);
void		data_is_zero_to_one(char *str, char *line);
void		data_is_in_degree_range(char *str, char *line);
void		data_is_in_rgb_range(char *str, char *line);
void		parse_data_set_rgb(char **data, int n, char *line);
void		error_malloc(void);

#endif
