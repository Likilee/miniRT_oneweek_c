/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:46:33 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:06:05 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		get_texture(t_scene *scene, char *line)
{
	char			**data;
	char			**albedo1;
	char			**albedo2;
	t_texture		*t;
	t_objects		*target;

	if (!(t = (t_texture *)malloc(sizeof(t_texture))))
		error_malloc();
	data = ft_split(line + 3, ' ');
	parse_error_data_count(data, 4, line);
	data_is_integer(data[0], line);
	if (ft_atoi(data[0]) < 0 || ft_atoi(data[0]) > 4)
		parse_error_identifier(line);
	albedo1 = ft_split(data[1], ',');
	parse_data_set_rgb(albedo1, 3, line);
	albedo2 = ft_split(data[2], ',');
	parse_data_set_rgb(albedo2, 3, line);
	data_is_double(data[3], line);
	t = texture(ft_atoi(data[0]), vdivide(color3(atod(albedo1[0]),
	atod(albedo1[1]), atod(albedo1[2])), 255), vdivide(color3(atod(albedo2[0]),
	atod(albedo2[1]), atod(albedo2[2])), 255), atod(data[3]));
	target = olast(scene->world);
	free(target->texture);
	target->texture = t;
	parse_free4(data, albedo1, albedo2, NULL);
}

void		get_texture_img(t_scene *scene, char *line, void *mlx)
{
	char			**data;
	t_data			*map;
	t_objects		*target;
	t_texture		*t;

	if (!(map = (t_data *)malloc(sizeof(t_data))))
		error_malloc();
	data = ft_split(line + 5, ' ');
	parse_error_data_count(data, 1, line);
	map->img = mlx_png_file_to_image(mlx, data[0], &map->width, &map->height);
	parse_error_img_filepath(map->img, line);
	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel,
								&map->size_line, &map->endian);
	t = texture_img(map);
	target = olast(scene->world);
	free(target->texture);
	target->texture = t;
	ft_free_arr(data);
}

void		get_resolution(t_scene *scene, char *line)
{
	char	**render_size;

	render_size = ft_split(line + 2, ' ');
	parse_data_set_double(render_size, 2, line);
	scene->canv = canvas(ft_atoi(render_size[0]), ft_atoi(render_size[1]));
	ft_free_arr(render_size);
}

void		get_ambient(t_scene *scene, char *line)
{
	char		**data;
	char		**rgb;
	double		ratio;
	t_color3	ambient;

	data = ft_split(line + 2, ' ');
	parse_error_data_count(data, 2, line);
	data_is_zero_to_one(data[0], line);
	ratio = atod(data[0]);
	rgb = ft_split(data[1], ',');
	parse_data_set_rgb(rgb, 3, line);
	ambient.x = ft_atoi(rgb[0]);
	ambient.y = ft_atoi(rgb[1]);
	ambient.z = ft_atoi(rgb[2]);
	ambient = vdivide(ambient, 255.0);
	ambient = vmult(ambient, ratio);
	scene->global.ambient = ambient;
	parse_free4(data, rgb, NULL, NULL);
}

void		get_camera(t_scene *scene, char *line)
{
	char		**data;
	char		**lookfrom;
	char		**lookdir;
	t_camera	*cam;
	double		hfov;

	data = ft_split(line + 2, ' ');
	parse_error_data_count(data, 3, line);
	lookfrom = ft_split(data[0], ',');
	parse_data_set_double(lookfrom, 3, line);
	lookdir = ft_split(data[1], ',');
	parse_data_set_zero_to_one(lookdir, 3, line);
	data_is_in_degree_range(data[2], line);
	hfov = atod(data[2]);
	cam = camera_init(to_vec3(lookfrom), to_vec3(lookdir), hfov);
	oadd(&scene->cam_list, object(CAM, cam, NULL, NULL));
	parse_free4(data, lookfrom, lookdir, NULL);
}
