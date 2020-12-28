#include "scene.h"

t_sphere	*sphere(t_point3 center, double radius, t_material *mat, t_texture *texture)
{
	t_sphere *sp;

	if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	sp->material = mat;
	sp->texture = texture;
	return (sp);
}

t_light		*light_point(t_point3 light_origin, t_color3 light_color, double ka)
{
	t_light	*light;

	if(!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->type = POINT;
	light->p = light_origin;
	light->light_color = light_color;
	light->ka = ka;
	return (light);
}

t_light		*light_parallel(t_vec3 dir, t_color3 light_color, double ka)
{
	t_light	*light;

	if(!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->type = PARALLEL;
	light->dir = vmult(vunit(dir), -1);
	light->ka = ka;
	light->light_color = light_color;
	return (light);
};

t_plane		*plane(t_point3 p, t_vec3 normal, t_material *mat, t_texture *texture)
{
	t_plane *pl;

	if(!(pl = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	pl->p = p;
	pl->normal = normal;
	pl->material = mat;
	pl->texture = texture;
	return (pl);
}

t_square	*square(t_point3 p, t_vec3 normal, double side_len, t_material *mat, t_texture *texture)
{
	t_square	*sq;
	double		half_side;

	if(!(sq = (t_square *)malloc(sizeof(t_square))))
		return (NULL);
	half_side = side_len / 2;
	sq->center = p;
	sq->normal = normal;
	sq->material = mat;
	sq->texture = texture;
	sq->side_len = side_len;
	if (fabs(normal.x) == 1.0)
	{
		sq->min = vminus(p, vec3(0, half_side, half_side));
		sq->max = vplus(p, vec3(0, half_side, half_side));
	}
	else if (fabs(normal.y) == 1.0)
	{
		sq->min = vminus(p, vec3(half_side, 0, half_side));
		sq->max = vplus(p, vec3(half_side, 0, half_side));
	}
	else if (fabs(normal.z) == 1.0)
	{
		sq->min = vminus(p, vec3(half_side, half_side, 0));
		sq->max = vplus(p, vec3(half_side, half_side, 0));
	}
	else
	{
		perror("Wrong normal intput to square!");
		exit(1);
	}
	return (sq);
}

t_cube	*cube(t_point3 center, double side_len, t_material *mat, t_texture *texture)
{
	t_cube *cb;
	double half_side;

	if (!(cb = (t_cube *)malloc(sizeof(t_cube))))
		return (NULL);
	half_side = side_len / 2;
	cb->center = center;
	cb->side_len = side_len;
	cb->texture = texture;
	cb->material = mat;
	cb->square[0] = square(vplus_(center, 0, half_side, 0), vec3(0,1,0), side_len, mat, texture);
	cb->square[1] = square(vplus_(center, 0, -half_side, 0), vec3(0,-1,0), side_len, mat, texture);
	cb->square[2] = square(vplus_(center, -half_side, 0, 0), vec3(-1,0,0), side_len, mat, texture);
	cb->square[3] = square(vplus_(center, half_side, 0, 0), vec3(1,0,0), side_len, mat, texture);
	cb->square[4] = square(vplus_(center, 0, 0, half_side), vec3(0,0,1), side_len, mat, texture);
	cb->square[5] = square(vplus_(center, 0, 0, -half_side), vec3(0,0,-1), side_len, mat, texture);
	return (cb);
}

t_pyramid *pyramid(t_point3 center, t_point3 top, double side_len, t_material *mat, t_texture *texture)
{
	t_pyramid	*pm;
	double 		half_side;
	t_point3	p1;
	t_point3	p2;
	t_point3	p3;
	t_point3	p4;

	if (!(pm = (t_pyramid *)malloc(sizeof(t_pyramid))))
		return (NULL);
	half_side = side_len / 2;
	pm->center = center;
	pm->top = top;
	pm->side_len = side_len;
	pm->texture = texture;
	pm->material = mat;
	p1 = vplus_(center, -half_side, 0, -half_side);
	p2 = vplus_(center, -half_side, 0, half_side);
	p3 = vplus_(center, half_side, 0, half_side);
	p4 = vplus_(center, half_side, 0, -half_side);
	pm->bottom = square(center, vec3(0,1,0), side_len, mat, texture);
	pm->side[0] = triangle(top, p1, p2, mat, texture);
	pm->side[1] = triangle(top, p2, p3, mat, texture);
	pm->side[2] = triangle(top, p3, p4, mat, texture);
	pm->side[3] = triangle(top, p4, p1, mat, texture);
	return (pm);
}

t_cylinder	*cylinder(t_point3 center_bottom, t_vec3 axis, double diameter, double height, t_material *mat, t_texture *texture)
{
	t_cylinder	*cy;

	if (!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cy->center_bottom = center_bottom;
	cy->center_top = vplus(center_bottom, vmult(axis, height));
	if (axis.x < 0 || axis.y < 0 || axis.z < 0)
	{
		cy->center_bottom = cy->center_top;
		cy->center_top = center_bottom;
	}
	cy->axis = axis;
	cy->radius = diameter / 2;
	cy->radius2 = cy->radius * cy->radius;
	cy->height = height;
	cy->material = mat;
	cy->texture = texture;
	return (cy);
}

t_triangle *triangle(t_point3 p0, t_point3 p1, t_point3 p2, t_material *mat, t_texture *texture)
{
	t_triangle	*tr;

	if (!(tr = (t_triangle *)malloc(sizeof(t_triangle))))
		return (NULL);
	tr->p0 = p0;
	tr->p1 = p1;
	tr->p2 = p2;
	tr->p0p1 = vminus(p1, p0);
	tr->p1p2 = vminus(p2, p1);
	tr->p2p0 = vminus(p0, p2);
	tr->normal = vunit(vcross(tr->p0p1, vminus(p2, p0)));
	tr->material = mat;
	tr->texture = texture;
	return (tr);
}

t_material	*material(t_material_type type, double option1)
{
	t_material *mat;

	if(!(mat = (t_material *)malloc(sizeof(t_material))))
		exit(1);
	mat->type = type;
	if (type == DIFFUSE)
		mat->option1 = option1;
	else if (type == LAMBERTIAN)
		mat->option1 = 0;
	else if (type == METAL)
	{
		if (option1 > 1)
			option1 = 1.0;
		mat->option1 = option1;
	}
	else if (type == DIELECTRIC)
		mat->option1 = option1;
	return (mat);
}

t_texture	*texture(t_texture_type type, t_color3 albedo1, t_color3 albedo2, double option1)
{
	t_texture *texture;

	if(!(texture = (t_texture *)malloc(sizeof(t_texture))))
		exit(1);
	texture->type = type;
	texture->albedo1 = albedo1;
	texture->albedo2 = albedo2;
	texture->option1 = option1;
	return (texture);
}

t_texture	*texture_img(t_texture_type type, t_data *img)
{
	t_texture *texture;

	if(!(texture = (t_texture *)malloc(sizeof(t_texture))))
		exit(1);
	texture->type = type;
	texture->albedo1 = color3(0,0,0);
	texture->albedo2 = color3(0,0,0);
	texture->option1 = 0;
	texture->img = img;
	return (texture);
}
