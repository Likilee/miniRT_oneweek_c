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

// 식별자 2글자인 애들부터 체크!
void		parse_rt(t_scene *scene, char *line)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, "R", 1))
		get_resolution(scene, line + 1);
	else if (ft_strnstr(line, "sp", 2))
		get_sphere(scene, line + 2);
	else if (ft_strnstr(line, "pl", 2))
		get_plane(scene, line + 2);
	else if (ft_strnstr(line, "sq", 2))
		get_square(scene, line + 2);
	else if (ft_strnstr(line, "cy", 2))
		get_cylinder(scene, line + 2);
	else if (ft_strnstr(line, "tr", 2))
		get_triangle(scene, line + 2);
	else if (ft_strnstr(line, "A", 1))
		get_ambient(scene, line + 1);
	else if (ft_strnstr(line, "c", 1))
		get_camera(scene, line + 1);
	else if (ft_strnstr(line, "l", 1))
		get_point_light(scene, line + 1);
}

void		get_resolution(t_scene *scene, char *line)
{
	char **render_size;

	render_size = ft_split(line, ' ');
	scene->canv = canvas(ft_atoi(render_size[0]), ft_atoi(render_size[1]));
	ft_free_arr(render_size, 2);
}

void		get_ambient(t_scene *scene, char *line)
{
	char		**data;
	char		**rgb;
	double		ratio;
	t_color3	ambient;

	data = ft_split(line, ' ');
	ratio = atod(data[0]);
	rgb = ft_split(data[1], ',');
	ambient.x = ft_atoi(rgb[0]);
	ambient.y = ft_atoi(rgb[1]);
	ambient.z = ft_atoi(rgb[2]);
	ambient = vdivide(ambient, 255.0);
	ambient = vmult(ambient, ratio);
	scene->global.ambient = ambient;
	ft_free_arr(rgb, 3);
	ft_free_arr(data, 2);
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

	data = ft_split(line, ' ');
	lookfrom = ft_split(data[0], ',');
	lookdir = ft_split(data[1], ',');
	look_from = point3(atod(lookfrom[0]), atod(lookfrom[1]), atod(lookfrom[2]));
	look_dir = vec3(atod(lookdir[0]), atod(lookdir[1]), atod(lookdir[2]));
	hfov = ft_atoi(data[2]);
	cam = camera_init(look_from, look_dir, hfov);
	oadd(&scene->cam_list, object(CAM, cam));
	ft_free_arr(data, 3);
	ft_free_arr(lookfrom, 3);
	ft_free_arr(lookdir, 3);
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
	data = ft_split(line, ' ');
	point = ft_split(data[0], ',');
	rgb = ft_split(data[2], ',');

	origin = point3(atod(point[0]), atod(point[1]), atod(point[2]));
	light_color = color3(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	light_color = vdivide(light_color, 255);
	light_color = vmult(light_color, atod(data[1]) * lux);
	oadd(&scene->world, object(LIGHT, light_point(origin, light_color, 0.1)));
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

	data = ft_split(line, ' ');
	center = ft_split(data[0], ',');
	albedo = ft_split(data[2], ',');
	sp_center = point3(atod(center[0]), atod(center[1]), atod(center[2]));
	sp_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	sp_albedo = vdivide(sp_albedo, 255);
	radius = atod(data[1]) * 0.5;
	solid = texture(SOLID, sp_albedo, sp_albedo, 0);
	diffuse = material(DIFFUSE, 0);
	oadd(&scene->world, object(SP, sphere(sp_center, radius, diffuse, solid)));
	ft_free_arr(data, 3);
	ft_free_arr(center, 3);
	ft_free_arr(albedo, 3);
}

void		get_plane(t_scene *scene, char *line)
{
	char		**data;
	char		**p;
	char		**n;
	char		**albedo;
	t_point3	point;
	t_vec3		normal;
	t_color3	pl_albedo;
	t_material	*diffuse;
	t_texture	*solid;

	data = ft_split(line, ' ');
	p = ft_split(data[0], ',');
	n = ft_split(data[1], ',');
	albedo = ft_split(data[2], ',');
	point = point3(atod(p[0]), atod(p[1]), atod(p[2]));
	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
	pl_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	pl_albedo = vdivide(pl_albedo, 255);
	solid = texture(SOLID, pl_albedo, pl_albedo, 0);
	diffuse = material(DIFFUSE, 0);
	oadd(&scene->world, object(PL, plane(point, normal, diffuse, solid)));
	ft_free_arr(data, 3);
	ft_free_arr(p, 3);
	ft_free_arr(n, 3);
	ft_free_arr(albedo, 3);
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

	data = ft_split(line, ' ');
	c = ft_split(data[0], ',');
	n = ft_split(data[1], ',');
	albedo = ft_split(data[3], ',');
	center = point3(atod(c[0]), atod(c[1]), atod(c[2]));
	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
	sq_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	sq_albedo = vdivide(sq_albedo, 255);
	solid = texture(SOLID, sq_albedo, sq_albedo, 0);
	diffuse = material(DIFFUSE, 0);
	oadd(&scene->world, object(SQ,
	square(center, normal, atod(data[2]), diffuse, solid)));
	ft_free_arr(data, 3);
	ft_free_arr(c, 3);
	ft_free_arr(n, 3);
	ft_free_arr(albedo, 3);
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

	data = ft_split(line, ' ');
	c = ft_split(data[0], ',');
	n = ft_split(data[1], ',');
	albedo = ft_split(data[4], ',');
	center = point3(atod(c[0]), atod(c[1]), atod(c[2]));
	normal = vec3(atod(n[0]), atod(n[1]), atod(n[2]));
	cy_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	cy_albedo = vdivide(cy_albedo, 255);
	solid = texture(SOLID, cy_albedo, cy_albedo, 0);
	diffuse = material(DIFFUSE, 0);
	oadd(&scene->world, object(CY,
	cylinder(center, normal, atod(data[2]), atod(data[3]), diffuse, solid)));
	ft_free_arr(data, 5);
	ft_free_arr(c, 3);
	ft_free_arr(n, 3);
	ft_free_arr(albedo, 3);
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
	data = ft_split(line, ' ');
	i = -1;
	while (++i < 3)
		p[i] = ft_split(data[i], ',');
	albedo = ft_split(data[3], ',');
	i = -1;
	while (++i < 3)
		pp[i] = point3(atod(p[i][0]), atod(p[i][1]), atod(p[i][2]));
	tr_albedo = color3(atod(albedo[0]), atod(albedo[1]), atod(albedo[2]));
	tr_albedo = vdivide(tr_albedo, 255);
	solid = texture(SOLID, tr_albedo, tr_albedo, 0);
	diffuse = material(DIFFUSE, 0);
	oadd(&scene->world, object(TR,
	triangle(pp[0], pp[1], pp[2], diffuse, solid)));
	ft_free_arr(data, 4);
	i = -1;
	while (++i < 3)
		ft_free_arr(p[i], 3);
	ft_free_arr(albedo, 3);
}