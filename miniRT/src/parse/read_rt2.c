/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:46:33 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:05:31 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_vec3		to_vec3(char **s)
{
	return (vec3(atod(s[0]), atod(s[1]), atod(s[2])));
}

void		parse_free4(char **a, char **b, char **c, char **d)
{
	ft_free_arr(a);
	ft_free_arr(b);
	ft_free_arr(c);
	ft_free_arr(d);
}

void		get_background(t_scene *scene, char *line, void *mlx)
{
	char			**data;
	t_data			*bg;
	t_texture		*t;
	t_material		*m;
	double			sidelen;

	if (!(bg = (t_data *)malloc(sizeof(t_data))))
		error_malloc();
	data = ft_split(line + 5, ' ');
	parse_error_data_count(data, 2, line);
	bg->img = mlx_png_file_to_image(mlx, data[0], &bg->width, &bg->height);
	parse_error_img_filepath(bg->img, line);
	data_is_double(data[1], line);
	sidelen = atod(data[1]);
	bg->addr = mlx_get_data_addr(bg->img, &bg->bits_per_pixel,
								&bg->size_line, &bg->endian);
	t = texture_img(bg);
	m = material(DIFFUSE, 0);
	scene->background = object(CB, cube(point3(0, 0, 0), sidelen), m, t);
	ft_free_arr(data);
}

void		get_lux(t_scene *scene, char *line)
{
	char			**data;

	data = ft_split(line + 2, ' ');
	parse_error_data_count(data, 1, line);
	data_is_integer(data[0], line);
	scene->global.lux = ft_atoi(data[0]);
	ft_free_arr(data);
}

void		get_material(t_scene *scene, char *line)
{
	char			**data;
	t_material		*m;
	t_material_type	type;
	t_objects		*target;

	data = ft_split(line + 3, ' ');
	parse_error_data_count(data, 2, line);
	data_is_integer(data[0], line);
	type = ft_atoi(data[0]);
	if (type < 0 || type > 3)
		parse_error_identifier(line);
	data_is_double(data[1], line);
	m = material(type, atod(data[1]));
	target = olast(scene->world);
	free(target->material);
	target->material = m;
	ft_free_arr(data);
}
