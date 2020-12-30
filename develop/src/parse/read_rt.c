#include "parse.h"

t_scene		*read_rt(char *filepath)
{
	t_scene *scene;
	int		fd;
	int		rd;
	char	*line;

	scene = scene_init();
	fd = open(filepath, O_RDONLY);
	rd = 1;
	while (rd)
	{
		rd = get_next_line(fd, &line);
		parse_rt(scene, line);
		free(line);
	}
	return (scene);
}
void		parse_rt(t_scene *scene, char *line)
{
	t_bool		result;

	result = parse_rt_header(scene, line);
	result = parse_rt_default(scene, line);
	result = parse_rt_bonus(scene, line);
	if  (result == FALSE)
		parse_error_identifier(line);
}

t_bool		parse_rt_header(t_scene *scene, char *line)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, "R ", 2))
		get_resolution(scene, line);
	else if (ft_strnstr(line, "A ", 2))
		get_ambient(scene, line);
	else if (*line != '\0')
		return (FALSE);
	return (TRUE);
}
// 식별자 2글자인 애들부터 체크!
t_bool		parse_rt_default(t_scene *scene, char *line)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, "sp ", 3))
		get_sphere(scene, line);
	else if (ft_strnstr(line, "pl ", 3))
		get_plane(scene, line);
	else if (ft_strnstr(line, "sq ", 3))
		get_square(scene, line);
	else if (ft_strnstr(line, "cy ", 3))
		get_cylinder(scene, line);
	else if (ft_strnstr(line, "tr ", 3))
		get_triangle(scene, line);
	else if (ft_strnstr(line, "c ", 2))
		get_camera(scene, line);
	else if (ft_strnstr(line, "l ", 2))
		get_point_light(scene, line);
	else
		return (FALSE);
	return (TRUE);
}

t_bool		parse_rt_bonus(t_scene *scene, char *line)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, "\tm ", 3))
		get_material(scene, line);
	else if (ft_strnstr(line, "\tt ", 3))
		get_texture(scene, line);
	else
		return (FALSE);
	return (TRUE);
};

void		get_material(t_scene *scene, char *line)
{
	char			**data;
	t_material		*m;
	t_material_type	type;
	t_objects		*target;

	data = ft_split(line + 3, ' ');
	parse_error_data_count(data, 2, line);
	if (ft_strncmp(data[0], "metal", 5) == 0)
		type = METAL;
	else if (ft_strncmp(data[0], "lambertian", 10) == 0)
		type = LAMBERTIAN;
	else if (ft_strncmp(data[0], "dielectric", 10) == 0)
		type = DIELECTRIC;
	else
		parse_error_identifier(line);
	data_is_double(data[1], line);
	m = material(type, atod(data[1]));
	target = olast(scene->world);
	free(target->
}
void		get_texture(t_scene *scene, char *line)
{}
void		get_resolution(t_scene *scene, char *line)
{
	char **render_size;

	render_size = ft_split(line + 2, ' ');
	parse_data_set_double(render_size, 2, line);
	scene->canv = canvas(ft_atoi(render_size[0]), ft_atoi(render_size[1]));
	ft_free_arr(render_size, 2);
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
	ft_free_arr(rgb, 3);
	ft_free_arr(data, 2);
}

static void		parse_free3(char **a, char **b, char **c)
{
	ft_free_arr(a, 3);
	ft_free_arr(b, 3);
	ft_free_arr(c, 3);
}
void		get_camera(t_scene *scene, char *line)
{
	char 		**data;
	char		**lookfrom;
	char		**lookdir;
	t_camera	*cam;
	t_point3	look_from;
	t_vec3		look_dir;
	double		hfov;

	data = ft_split(line + 2, ' ');
	parse_error_data_count(data, 3, line);
	lookfrom = ft_split(data[0], ',');
	parse_data_set_double(lookfrom, 3, line);
	lookdir = ft_split(data[1], ',');
	parse_data_set_zero_to_one(lookdir, 3, line);
	look_from = point3(atod(lookfrom[0]), atod(lookfrom[1]), atod(lookfrom[2]));
	look_dir = vec3(atod(lookdir[0]), atod(lookdir[1]), atod(lookdir[2]));
	data_is_in_degree_range(data[2], line);
	hfov = atod(data[2]);
	cam = camera_init(look_from, look_dir, hfov);
	oadd(&scene->cam_list, object(CAM, cam, NULL, NULL));
	parse_free3(data, lookfrom, lookdir);
}

void		get_point_light(t_scene *scene, char *line)
{
	char 		**data;
	char		**point;
	char		**rgb;
	t_point3	origin;
	t_color3	light_color;
	double		lux;
	double		ka;

	lux = 50;
	ka = 0.1;
	data = ft_split(line + 2, ' ');
	point = ft_split(data[0], ',');
	rgb = ft_split(data[2], ',');
	parse_error_data_count(data, 3, line);
	parse_data_set_double(point, 3, line);
	data_is_zero_to_one(data[1], line);
	parse_data_set_rgb(rgb, 3, line);
	origin = point3(atod(point[0]), atod(point[1]), atod(point[2]));
	light_color = color3(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	light_color = vdivide(light_color, 255);
	light_color = vmult(light_color, atod(data[1]) * lux);
	oadd(&scene->world, object(LIGHT, light_point(origin, light_color, 0.1, atod(data[1])), NULL, NULL));
	ft_free_arr(data, 3);
	ft_free_arr(point, 3);
	ft_free_arr(rgb, 3);
}

void		get_sphere(t_scene *scene, char *line)
{
	char		**data;
	char		**center;
	char		**albedo;
	t_point3	sp_center;
	t_color3	sp_albedo;
	double		radius;
	t_material	*diffuse;
	t_texture	*solid;

	data = ft_split(line + 3, ' ');
	center = ft_split(data[0], ',');
	albedo = ft_split(data[2], ',');
	parse_error_data_count(data, 3, line);
	parse_data_set_double(center, 3, line);
	data_is_double(data[1], line);
	parse_data_set_rgb(albedo, 3, line);
	sp_center = point3(atod(center[0]), atod(center[1]), atod(center[2]));
	sp_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	sp_albedo = vdivide(sp_albedo, 255);
	radius = atod(data[1]) * 0.5;
	solid = texture(SOLID, sp_albedo, sp_albedo, 0);
	diffuse = material(DIFFUSE, 0);
	oadd(&scene->world, object(SP, sphere(sp_center, radius), diffuse, solid));
	parse_free3(data, center, albedo);
}

void		get_plane(t_scene *scene, char *line)
{
	char		**data;
	char		**p;
	char		**n;
	char		**al;
	t_point3	point;
	t_vec3		normal;
	t_color3	pl_albedo;
	t_material	*diffuse;
	t_texture	*solid;

	data = ft_split(line + 3, ' ');
	p = ft_split(data[0], ',');
	n = ft_split(data[1], ',');
	al = ft_split(data[2], ',');
	parse_error_data_count(data, 3, line);
	parse_data_set_double(p, 3, line);
	parse_data_set_zero_to_one(n, 3, line);
	parse_data_set_rgb(al, 3, line);
	point = point3(atod(p[0]), atod(p[1]), atod(p[2]));
	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
	pl_albedo = vdivide(color3(atod(al[0]), atod(al[1]), atod(al[2])), 255);
	solid = texture(SOLID, pl_albedo, pl_albedo, 0);
	diffuse = material(DIFFUSE, 32);
	oadd(&scene->world, object(PL, plane(point, normal), diffuse, solid));
	ft_free_arr(data, 3);
	parse_free3(p, n, al);
}

void		get_square(t_scene *scene, char *line)
{
	char			**data;
	char			**c;
	char			**n;
	char			**albedo;
	t_point3		center;
	t_vec3			normal;
	t_color3		sq_albedo;
	t_material		*diffuse;
	t_texture		*solid;

	data = ft_split(line + 3, ' ');
	c = ft_split(data[0], ',');
	n = ft_split(data[1], ',');
	albedo = ft_split(data[3], ',');
	parse_error_data_count(data, 4, line);
	parse_data_set_double(c, 3, line);
	parse_data_set_zero_to_one(n, 3, line);
	data_is_double(data[2], line);
	parse_data_set_rgb(albedo, 3, line);
	center = point3(atod(c[0]), atod(c[1]), atod(c[2]));
	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
	sq_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	sq_albedo = vdivide(sq_albedo, 255);
	solid = texture(SOLID, sq_albedo, sq_albedo, 0);
	diffuse = material(DIFFUSE, 32);
	oadd(&scene->world, object(SQ,
	square(center, normal, atod(data[2])), diffuse, solid));
	ft_free_arr(data, 3);
	parse_free3(c, n, albedo);
}

void		get_cylinder(t_scene *scene, char *line)
{
	char			**data;
	char			**c;
	char			**n;
	char			**albedo;
	t_point3		center;
	t_vec3			normal;
	t_color3		cy_albedo;
	t_material		*diffuse;
	t_texture		*solid;

	data = ft_split(line + 3, ' ');
	c = ft_split(data[0], ',');
	n = ft_split(data[1], ',');
	albedo = ft_split(data[4], ',');
	parse_error_data_count(data, 5, line);
	parse_data_set_double(c, 3, line);
	parse_data_set_zero_to_one(n, 3, line);
	data_is_double(data[2], line);
	data_is_double(data[3], line);
	parse_data_set_rgb(albedo, 3, line);
	center = point3(atod(c[0]), atod(c[1]), atod(c[2]));
	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
	cy_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	cy_albedo = vdivide(cy_albedo, 255);
	solid = texture(SOLID, cy_albedo, cy_albedo, 0);
	diffuse = material(DIFFUSE, 32);
	oadd(&scene->world, object(CY,
	cylinder(center, normal, atod(data[2]), atod(data[3])), diffuse, solid));
	ft_free_arr(data, 5);
	parse_free3(c, n, albedo);
}

void		get_triangle(t_scene *scene, char *line)
{
	char			**data;
	char			**p[3];
	char			**albedo;
	t_point3		pp[3];
	t_color3		tr_albedo;
	t_material		*diffuse;
	t_texture		*solid;
	int				i;

	data = ft_split(line + 3, ' ');
	i = -1;
	while (++i < 3)
	{
		p[i] = ft_split(data[i], ',');
		parse_data_set_double(p[i], 3, line);
	}
	albedo = ft_split(data[3], ',');
	parse_data_set_rgb(albedo, 3, line);
	i = -1;
	while (++i < 3)
		pp[i] = point3(atod(p[i][0]), atod(p[i][1]), atod(p[i][2]));
	tr_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	tr_albedo = vdivide(tr_albedo, 255);
	solid = texture(SOLID, tr_albedo, tr_albedo, 0);
	diffuse = material(DIFFUSE, 32);
	oadd(&scene->world, object(TR,
	triangle(pp[0], pp[1], pp[2]), diffuse, solid));
	ft_free_arr(data, 4);
	parse_free3(p[0], p[1], p[2]);
	ft_free_arr(albedo, 3);
}
