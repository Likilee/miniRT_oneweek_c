/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:46:33 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 23:08:27 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		get_triangle(t_scene *scene, char *line)
{
	char			**data[5];
	t_point3		pp[3];
	t_material		*diffuse;
	t_texture		*solid;
	int				i;

	data[0] = ft_split(line + 3, ' ');
	parse_error_data_count(data[0], 4, line);
	i = -1;
	while (++i < 3)
	{
		data[i + 1] = ft_split(data[0][i], ',');
		parse_data_set_double(data[i + 1], 3, line);
	}
	data[4] = ft_split(data[0][3], ',');
	parse_data_set_rgb(data[4], 3, line);
	i = -1;
	while (++i < 3)
		pp[i] = to_vec3(data[i + 1]);
	solid = texture(SOLID, vdivide(to_vec3(data[4]), 255), color3(0, 0, 0), 0);
	diffuse = material(DIFFUSE, KSN);
	oadd(&scene->world, object(TR,
	triangle(pp[0], pp[1], pp[2]), diffuse, solid));
	parse_free4(data[0], data[1], data[2], data[3]);
	ft_free_arr(data[4]);
}

void		get_cube(t_scene *scene, char *line)
{
	char			**data;
	char			**center;
	char			**albedo;
	t_material		*diffuse;
	t_texture		*solid;

	data = ft_split(line + 3, ' ');
	parse_error_data_count(data, 3, line);
	center = ft_split(data[0], ',');
	parse_data_set_double(center, 3, line);
	data_is_double(data[1], line);
	albedo = ft_split(data[2], ',');
	parse_data_set_rgb(albedo, 3, line);
	solid = texture(SOLID, vdivide(to_vec3(albedo), 255), color3(0, 0, 0), 0);
	diffuse = material(DIFFUSE, KSN);
	oadd(&scene->world, object(CB,
		cube(to_vec3(center), atod(data[1])), diffuse, solid));
	parse_free4(data, center, albedo, NULL);
}

/*
** data[0] : Splited data set
** data[1] : bottom;
** data[2] : top;
** data[3] : albedo;
** data[0][2] : side_len
*/

void		get_pyramid(t_scene *scene, char *line)
{
	char			**data[4];
	t_material		*diffuse;
	t_texture		*solid;

	data[0] = ft_split(line + 3, ' ');
	parse_error_data_count(data[0], 4, line);
	data[1] = ft_split(data[0][0], ',');
	parse_data_set_double(data[1], 3, line);
	data[2] = ft_split(data[0][1], ',');
	parse_data_set_double(data[2], 3, line);
	data_is_double(data[0][2], line);
	data[3] = ft_split(data[0][3], ',');
	parse_data_set_rgb(data[3], 3, line);
	solid = texture(SOLID, vdivide(to_vec3(data[3]), 255), color3(0, 0, 0), 0);
	diffuse = material(DIFFUSE, KSN);
	oadd(&scene->world, object(PM, pyramid(to_vec3(data[1]), to_vec3(data[2]),
											atod(data[0][2])), diffuse, solid));
	parse_free4(data[0], data[1], data[2], data[3]);
}

void		get_parallel_light(t_scene *scene, char *line)
{
	char		**data;
	char		**d;
	char		**rgb;
	t_vec3		dir;
	t_color3	light;

	data = ft_split(line + 2, ' ');
	parse_error_data_count(data, 3, line);
	d = ft_split(data[0], ',');
	parse_data_set_double(d, 3, line);
	data_is_zero_to_one(data[1], line);
	rgb = ft_split(data[2], ',');
	parse_data_set_rgb(rgb, 3, line);
	dir = vec3(atod(d[0]), atod(d[1]), atod(d[2]));
	light = vec3(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	light = vdivide(light, 255);
	light = vmult(light, atod(data[1]));
	oadd(&scene->world, object(LIGHT,
				light_parallel(dir, light, 0.1, atod(data[1])), NULL, NULL));
	parse_free4(data, d, rgb, NULL);
}
