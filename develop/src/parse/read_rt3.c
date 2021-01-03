// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   read_rt3.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/01/03 22:30:55 by kihoonlee         #+#    #+#             */
// /*   Updated: 2021/01/04 00:53:07 by kihoonlee        ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "parse.h"

// t_vec3		to_vec3(char **s)
// {
// 	return (vec3(atod(s[0]), atod(s[1]), atod(s[2])));
// }

// void		parse_free4(char **a, char **b, char **c, char **d)
// {
// 	ft_free_arr(a);
// 	ft_free_arr(b);
// 	ft_free_arr(c);
// 	ft_free_arr(d);
// }

// void		get_background(t_scene *scene, char *line, void *mlx)
// {
// 	char			**data;
// 	t_data			*bg;
// 	t_texture		*t;
// 	t_material		*m;
// 	double			sidelen;

// 	if (!(bg = (t_data *)malloc(sizeof(t_data))))
// 		error_malloc();
// 	data = ft_split(line + 5, ' ');
// 	parse_error_data_count(data, 2, line);
// 	bg->img = mlx_png_file_to_image(mlx, data[0], &bg->width, &bg->height);
// 	parse_error_img_filepath(bg->img, line);
// 	data_is_double(data[1], line);
// 	sidelen = atod(data[1]);
// 	bg->addr = mlx_get_data_addr(bg->img, &bg->bits_per_pixel,
// 								&bg->size_line, &bg->endian);
// 	t = texture_img(bg);
// 	m = material(DIFFUSE, 0);
// 	scene->background = object(CB, cube(point3(0, 0, 0), sidelen), m, t);
// 	ft_free_arr(data);
// }

// void		get_lux(t_scene *scene, char *line)
// {
// 	char			**data;

// 	data = ft_split(line + 2, ' ');
// 	parse_error_data_count(data, 1, line);
// 	data_is_integer(data[0], line);
// 	scene->global.lux = ft_atoi(data[0]);
// 	ft_free_arr(data);
// }

// void		get_material(t_scene *scene, char *line)
// {
// 	char			**data;
// 	t_material		*m;
// 	t_material_type	type;
// 	t_objects		*target;

// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 2, line);
// 	data_is_integer(data[0], line);
// 	type = ft_atoi(data[0]);
// 	if (type < 0 || type > 3)
// 		parse_error_identifier(line);
// 	data_is_double(data[1], line);
// 	m = material(type, atod(data[1]));
// 	target = olast(scene->world);
// 	free(target->material);
// 	target->material = m;
// 	ft_free_arr(data);
// }

// void		get_texture(t_scene *scene, char *line)
// {
// 	char			**data;
// 	char			**albedo1;
// 	char			**albedo2;
// 	t_texture		*t;
// 	t_objects		*target;

// 	if (!(t = (t_texture *)malloc(sizeof(t_texture))))
// 		error_malloc();
// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 4, line);
// 	data_is_integer(data[0], line);
// 	if (ft_atoi(data[0]) < 0 || ft_atoi(data[0]) > 4)
// 		parse_error_identifier(line);
// 	albedo1 = ft_split(data[1], ',');
// 	parse_data_set_rgb(albedo1, 3, line);
// 	albedo2 = ft_split(data[2], ',');
// 	parse_data_set_rgb(albedo2, 3, line);
// 	data_is_double(data[3], line);
// 	t = texture(ft_atoi(data[0]), vdivide(color3(atod(albedo1[0]),
// 	atod(albedo1[1]), atod(albedo1[2])), 255), vdivide(color3(atod(albedo2[0]),
// 	atod(albedo2[1]), atod(albedo2[2])), 255), atod(data[3]));
// 	target = olast(scene->world);
// 	free(target->texture);
// 	target->texture = t;
// 	parse_free4(data, albedo1, albedo2, NULL);
// }

// void		get_texture_img(t_scene *scene, char *line, void *mlx)
// {
// 	char			**data;
// 	t_data			*map;
// 	t_objects		*target;
// 	t_texture		*t;

// 	if (!(map = (t_data *)malloc(sizeof(t_data))))
// 		error_malloc();
// 	data = ft_split(line + 5, ' ');
// 	parse_error_data_count(data, 1, line);
// 	map->img = mlx_png_file_to_image(mlx, data[0], &map->width, &map->height);
// 	parse_error_img_filepath(map->img, line);
// 	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel,
// 								&map->size_line, &map->endian);
// 	t = texture_img(map);
// 	target = olast(scene->world);
// 	free(target->texture);
// 	target->texture = t;
// 	ft_free_arr(data);
// }

// void		get_resolution(t_scene *scene, char *line)
// {
// 	char	**render_size;

// 	render_size = ft_split(line + 2, ' ');
// 	parse_data_set_double(render_size, 2, line);
// 	scene->canv = canvas(ft_atoi(render_size[0]), ft_atoi(render_size[1]));
// 	ft_free_arr(render_size);
// }

// void		get_ambient(t_scene *scene, char *line)
// {
// 	char		**data;
// 	char		**rgb;
// 	double		ratio;
// 	t_color3	ambient;

// 	data = ft_split(line + 2, ' ');
// 	parse_error_data_count(data, 2, line);
// 	data_is_zero_to_one(data[0], line);
// 	ratio = atod(data[0]);
// 	rgb = ft_split(data[1], ',');
// 	parse_data_set_rgb(rgb, 3, line);
// 	ambient.x = ft_atoi(rgb[0]);
// 	ambient.y = ft_atoi(rgb[1]);
// 	ambient.z = ft_atoi(rgb[2]);
// 	ambient = vdivide(ambient, 255.0);
// 	ambient = vmult(ambient, ratio);
// 	scene->global.ambient = ambient;
// 	parse_free4(data, rgb, NULL, NULL);
// }

// void		get_camera(t_scene *scene, char *line)
// {
// 	char		**data;
// 	char		**lookfrom;
// 	char		**lookdir;
// 	t_camera	*cam;
// 	double		hfov;

// 	data = ft_split(line + 2, ' ');
// 	parse_error_data_count(data, 3, line);
// 	lookfrom = ft_split(data[0], ',');
// 	parse_data_set_double(lookfrom, 3, line);
// 	lookdir = ft_split(data[1], ',');
// 	parse_data_set_zero_to_one(lookdir, 3, line);
// 	data_is_in_degree_range(data[2], line);
// 	hfov = atod(data[2]);
// 	cam = camera_init(to_vec3(lookfrom), to_vec3(lookdir), hfov);
// 	oadd(&scene->cam_list, object(CAM, cam, NULL, NULL));
// 	parse_free4(data, lookfrom, lookdir, NULL);
// }

// void		get_point_light(t_scene *scene, char *line)
// {
// 	char		**data;
// 	char		**point;
// 	char		**rgb;
// 	t_color3	light_color;
// 	double		lux;

// 	lux = scene->global.lux;
// 	data = ft_split(line + 2, ' ');
// 	parse_error_data_count(data, 3, line);
// 	point = ft_split(data[0], ',');
// 	parse_data_set_double(point, 3, line);
// 	data_is_zero_to_one(data[1], line);
// 	rgb = ft_split(data[2], ',');
// 	parse_data_set_rgb(rgb, 3, line);
// 	light_color = color3(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
// 	light_color = vdivide(light_color, 255);
// 	light_color = vmult(light_color, atod(data[1]) * lux);
// 	oadd(&scene->world, object(LIGHT, light_point(to_vec3(point),
// 				light_color, 0.1, atod(data[1])), NULL, NULL));
// 	parse_free4(data, point, rgb, NULL);
// }

// /*
// ** data[0] : Splited data set
// ** data[1] : Center (double,3)
// ** data[2] : Albedo (rgb,3)
// ** data[0][1] : Radius (double)
// */

// void		get_sphere(t_scene *scene, char *line)
// {
// 	char		**data[3];
// 	double		radius;
// 	t_material	*diffuse;
// 	t_texture	*solid;

// 	data[0] = ft_split(line + 3, ' ');
// 	parse_error_data_count(data[0], 3, line);
// 	data[1] = ft_split(data[0][0], ',');
// 	parse_data_set_double(data[1], 3, line);
// 	data[2] = ft_split(data[0][2], ',');
// 	parse_data_set_rgb(data[2], 3, line);
// 	data_is_double(data[0][1], line);
// 	radius = atod(data[0][1]) * 0.5;
// 	solid = texture(SOLID, vdivide(to_vec3(data[2]), 255), color3(0, 0, 0), 0);
// 	diffuse = material(DIFFUSE, 0);
// 	oadd(&scene->world, object(SP,
// 		sphere(to_vec3(data[1]), radius), diffuse, solid));
// 	parse_free4(data[0], data[1], data[2], NULL);
// }

// /*
// ** data[0] : Splited data set
// ** data[1]
// */

// void		get_plane(t_scene *scene, char *line)
// {
// 	char		**data;
// 	char		**p;
// 	char		**n;
// 	char		**al;
// 	t_point3	point;
// 	t_vec3		normal;
// 	t_color3	pl_albedo;
// 	t_material	*diffuse;
// 	t_texture	*solid;

// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 3, line);
// 	p = ft_split(data[0], ',');
// 	parse_data_set_double(p, 3, line);
// 	n = ft_split(data[1], ',');
// 	parse_data_set_zero_to_one(n, 3, line);
// 	al = ft_split(data[2], ',');
// 	parse_data_set_rgb(al, 3, line);
// 	point = point3(atod(p[0]), atod(p[1]), atod(p[2]));
// 	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
// 	pl_albedo = vdivide(color3(atod(al[0]), atod(al[1]), atod(al[2])), 255);
// 	solid = texture(SOLID, pl_albedo, pl_albedo, 0);
// 	diffuse = material(DIFFUSE, 32);
// 	oadd(&scene->world, object(PL, plane(point, normal), diffuse, solid));
// 	parse_free4(data, p, n, al);
// }

// void		get_square(t_scene *scene, char *line)
// {
// 	char			**data;
// 	char			**c;
// 	char			**n;
// 	char			**albedo;
// 	t_point3		center;
// 	t_vec3			normal;
// 	t_color3		sq_albedo;
// 	t_material		*diffuse;
// 	t_texture		*solid;

// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 4, line);
// 	c = ft_split(data[0], ',');
// 	parse_data_set_double(c, 3, line);
// 	n = ft_split(data[1], ',');
// 	parse_data_set_zero_to_one(n, 3, line);
// 	albedo = ft_split(data[3], ',');
// 	data_is_double(data[2], line);
// 	// parse_data_set_rgb(albedo, 3, line);
// 	center = point3(atod(c[0]), atod(c[1]), atod(c[2]));
// 	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
// 	sq_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
// 	sq_albedo = vdivide(sq_albedo, 255);
// 	solid = texture(SOLID, sq_albedo, sq_albedo, 0);
// 	diffuse = material(DIFFUSE, 32);
// 	oadd(&scene->world, object(SQ,
// 	square(center, normal, atod(data[2])), diffuse, solid));
// 	parse_free4(data, c, n, albedo);
// }

// void		get_cylinder(t_scene *scene, char *line)
// {
// 	char			**data;
// 	char			**c;
// 	char			**n;
// 	char			**albedo;
// 	t_point3		center;
// 	t_vec3			normal;
// 	t_color3		cy_albedo;
// 	t_material		*diffuse;
// 	t_texture		*solid;

// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 5, line);
// 	c = ft_split(data[0], ',');
// 	parse_data_set_double(c, 3, line);
// 	n = ft_split(data[1], ',');
// 	parse_data_set_zero_to_one(n, 3, line);
// 	data_is_double(data[2], line);
// 	data_is_double(data[3], line);
// 	albedo = ft_split(data[4], ',');
// 	parse_data_set_rgb(albedo, 3, line);
// 	center = point3(atod(c[0]), atod(c[1]), atod(c[2]));
// 	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
// 	cy_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
// 	cy_albedo = vdivide(cy_albedo, 255);
// 	solid = texture(SOLID, cy_albedo, cy_albedo, 0);
// 	diffuse = material(DIFFUSE, 32);
// 	oadd(&scene->world, object(CY,
// 	cylinder(center, normal, atod(data[2]), atod(data[3])), diffuse, solid));
// 	parse_free4(data, c, n, albedo);
// }

// void		get_triangle(t_scene *scene, char *line)
// {
// 	char			**data;
// 	char			**p[3];
// 	char			**albedo;
// 	t_point3		pp[3];
// 	t_color3		tr_albedo;
// 	t_material		*diffuse;
// 	t_texture		*solid;
// 	int				i;

// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 4, line);
// 	i = -1;
// 	while (++i < 3)
// 	{
// 		p[i] = ft_split(data[i], ',');
// 		parse_data_set_double(p[i], 3, line);
// 	}
// 	albedo = ft_split(data[3], ',');
// 	parse_data_set_rgb(albedo, 3, line);
// 	i = -1;
// 	while (++i < 3)
// 		pp[i] = point3(atod(p[i][0]), atod(p[i][1]), atod(p[i][2]));
// 	tr_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
// 	tr_albedo = vdivide(tr_albedo, 255);
// 	solid = texture(SOLID, tr_albedo, tr_albedo, 0);
// 	diffuse = material(DIFFUSE, 32);
// 	oadd(&scene->world, object(TR,
// 	triangle(pp[0], pp[1], pp[2]), diffuse, solid));
// 	ft_free_arr(data);
// 	parse_free4(p[0], p[1], p[2], albedo);
// }

// void		get_cube(t_scene *scene, char *line)
// {
// 	char			**data;
// 	char			**c;
// 	char			**a;
// 	t_material		*diffuse;
// 	t_texture		*solid;
// 	t_color3		albedo;

// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 3, line);
// 	c = ft_split(data[0], ',');
// 	parse_data_set_double(c, 3, line);
// 	data_is_double(data[1], line);
// 	a = ft_split(data[2], ',');
// 	parse_data_set_rgb(a, 3, line);
// 	albedo = color3(atod(a[0]), atod(a[1]), atod(a[2]));
// 	albedo = vdivide(albedo, 255);
// 	solid = texture(SOLID, albedo, albedo, 0);
// 	diffuse = material(DIFFUSE, 32);
// 	oadd(&scene->world, object(CB,
// 		cube(point3(atod(c[0]), atod(c[1]), atod(c[2])), atod(data[1])),
// 		diffuse, solid));
// 	parse_free4(data, c, a, NULL);
// }

// void		get_pyramid(t_scene *scene, char *line)
// {
// 	char			**data;
// 	char			**b;
// 	char			**t;
// 	char			**a;
// 	t_material		*diffuse;
// 	t_texture		*solid;
// 	t_color3		albedo;

// 	data = ft_split(line + 3, ' ');
// 	parse_error_data_count(data, 4, line);
// 	b = ft_split(data[0], ',');
// 	parse_data_set_double(b, 3, line);
// 	t = ft_split(data[1], ',');
// 	parse_data_set_double(t, 3, line);
// 	data_is_double(data[2], line);
// 	a = ft_split(data[3], ',');
// 	parse_data_set_rgb(a, 3, line);
// 	albedo = vdivide(color3(atod(a[0]), atod(a[1]), atod(a[2])), 255);
// 	solid = texture(SOLID, albedo, albedo, 0);
// 	diffuse = material(DIFFUSE, 32);
// 	oadd(&scene->world,
// 	object(PM, pyramid(point3(atod(b[0]), atod(b[1]), atod(b[2])),
// 				point3(atod(t[0]), atod(t[1]), atod(t[2])),
// 				atod(data[2])), diffuse, solid));
// 	parse_free4(data, b, t, a);
// }

// void		get_parallel_light(t_scene *scene, char *line)
// {
// 	char		**data;
// 	char		**d;
// 	char		**rgb;
// 	t_vec3		dir;
// 	t_color3	light;

// 	data = ft_split(line + 2, ' ');
// 	parse_error_data_count(data, 3, line);
// 	d = ft_split(data[0], ',');
// 	parse_data_set_double(d, 3, line);
// 	data_is_zero_to_one(data[1], line);
// 	rgb = ft_split(data[2], ',');
// 	parse_data_set_rgb(rgb, 3, line);
// 	dir = vec3(atod(d[0]), atod(d[1]), atod(d[2]));
// 	light = vec3(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
// 	light = vdivide(light, 255);
// 	light = vmult(light, atod(data[1]));
// 	oadd(&scene->world, object(LIGHT, light_parallel(dir, light, 0.1, atod(data[1])), NULL, NULL));
// 	parse_free4(data, d, rgb, NULL);
// }
