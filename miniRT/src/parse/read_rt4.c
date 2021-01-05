/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:46:33 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 23:08:27 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		get_point_light(t_scene *scene, char *line)
{
	char		**data;
	char		**point;
	char		**rgb;
	t_color3	light_color;
	double		lux;

	lux = scene->global.lux;
	data = ft_split(line + 2, ' ');
	parse_error_data_count(data, 3, line);
	point = ft_split(data[0], ',');
	parse_data_set_double(point, 3, line);
	data_is_zero_to_one(data[1], line);
	rgb = ft_split(data[2], ',');
	parse_data_set_rgb(rgb, 3, line);
	light_color = color3(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	light_color = vdivide(light_color, 255);
	light_color = vmult(light_color, atod(data[1]) * lux);
	oadd(&scene->world, object(LIGHT, light_point(to_vec3(point),
				light_color, 0.1, atod(data[1])), NULL, NULL));
	parse_free4(data, point, rgb, NULL);
}

/*
** data[0] : Splited data set
** data[1] : Center (double,3)
** data[2] : Albedo (rgb,3)
** data[0][1] : Radius (double)
*/

void		get_sphere(t_scene *scene, char *line)
{
	char		**data[3];
	double		radius;
	t_material	*diffuse;
	t_texture	*solid;

	data[0] = ft_split(line + 3, ' ');
	parse_error_data_count(data[0], 3, line);
	data[1] = ft_split(data[0][0], ',');
	parse_data_set_double(data[1], 3, line);
	data[2] = ft_split(data[0][2], ',');
	parse_data_set_rgb(data[2], 3, line);
	data_is_double(data[0][1], line);
	radius = atod(data[0][1]) * 0.5;
	solid = texture(SOLID, vdivide(to_vec3(data[2]), 255), color3(0, 0, 0), 0);
	diffuse = material(DIFFUSE, 0);
	oadd(&scene->world, object(SP,
		sphere(to_vec3(data[1]), radius), diffuse, solid));
	parse_free4(data[0], data[1], data[2], NULL);
}

/*
** data[0] : Splited data set
** data[1] : 한점 p (double3)
** data[2] : 법선 n (double3)
** data[3] : albedo (rgb3)
*/

void		get_plane(t_scene *scene, char *line)
{
	char		**data[4];
	t_point3	point;
	t_vec3		normal;
	t_material	*diffuse;
	t_texture	*solid;

	data[0] = ft_split(line + 3, ' ');
	parse_error_data_count(data[0], 3, line);
	data[1] = ft_split(data[0][0], ',');
	parse_data_set_double(data[1], 3, line);
	data[2] = ft_split(data[0][1], ',');
	parse_data_set_zero_to_one(data[2], 3, line);
	data[3] = ft_split(data[0][2], ',');
	parse_data_set_rgb(data[3], 3, line);
	point = point3(atod(data[1][0]), atod(data[1][1]), atod(data[1][2]));
	normal = vec3(atod(data[2][0]), atod(data[2][1]), atod(data[2][2]));
	solid = texture(SOLID, vdivide(to_vec3(data[3]), 255), color3(0, 0, 0), 0);
	diffuse = material(DIFFUSE, KSN);
	oadd(&scene->world, object(PL, plane(point, normal), diffuse, solid));
	parse_free4(data[0], data[1], data[2], data[3]);
}

/*
** data[0] : Splited data set
** data[1] : center;
** data[2] : normal;
** data[3] : albedo;
** data[0][2] : side_len;
*/

void		get_square(t_scene *scene, char *line)
{
	char			**data[4];
	t_material		*diffuse;
	t_texture		*solid;

	data[0] = ft_split(line + 3, ' ');
	parse_error_data_count(data[0], 4, line);
	data[1] = ft_split(data[0][0], ',');
	parse_data_set_double(data[1], 3, line);
	data[2] = ft_split(data[0][1], ',');
	parse_data_set_zero_to_one(data[2], 3, line);
	data[3] = ft_split(data[0][3], ',');
	data_is_double(data[0][2], line);
	solid = texture(SOLID, vdivide(to_vec3(data[3]), 255), color3(0, 0, 0), 0);
	diffuse = material(DIFFUSE, 32);
	oadd(&scene->world, object(SQ,
	square(to_vec3(data[1]), to_vec3(data[2]),
			atod(data[0][2])), diffuse, solid));
	parse_free4(data[0], data[1], data[2], data[3]);
}

/*
** data[0] : Splited data set
** data[1] : center;
** data[2] : normal;
** data[3] : albedo;
** data[0][2] : radius;
** data[0][3] : height;
*/

void		get_cylinder(t_scene *scene, char *line)
{
	char			**data[4];
	t_material		*diffuse;
	t_texture		*solid;

	data[0] = ft_split(line + 3, ' ');
	parse_error_data_count(data[0], 5, line);
	data[1] = ft_split(data[0][0], ',');
	parse_data_set_double(data[1], 3, line);
	data[2] = ft_split(data[0][1], ',');
	parse_data_set_zero_to_one(data[2], 3, line);
	data_is_double(data[0][2], line);
	data_is_double(data[0][3], line);
	data[3] = ft_split(data[0][4], ',');
	parse_data_set_rgb(data[3], 3, line);
	solid = texture(SOLID, vdivide(to_vec3(data[3]), 255), color3(0, 0, 0), 0);
	diffuse = material(DIFFUSE, 32);
	oadd(&scene->world, object(CY,
	cylinder(to_vec3(data[1]), to_vec3(data[2]), atod(data[0][2]),
				atod(data[0][3])), diffuse, solid));
	parse_free4(data[0], data[1], data[2], data[3]);
}
