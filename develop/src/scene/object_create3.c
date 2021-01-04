/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:27:12 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:48:33 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_bool		check_axis_align(t_vec3 *axis)
{
	if (fabs(axis->x) != 1 && fabs(axis->y) != 1 && fabs(axis->z) != 1)
		return (FALSE);
	else if (vlength2(*axis) != 1)
		return (FALSE);
	return (TRUE);
}

t_cylinder	*cylinder(t_point3 bottom, t_vec3 axis, double d, double height)
{
	t_cylinder	*cy;

	if (!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
		error_malloc();
	cy->center_bottom = bottom;
	cy->center_top = vplus(bottom, vmult(axis, height));
	if (axis.x < 0 || axis.y < 0 || axis.z < 0)
	{
		cy->center_bottom = cy->center_top;
		cy->center_top = bottom;
	}
	cy->axis = axis;
	if (check_axis_align(&axis) == FALSE)
	{
		perror("Wrong normal intput to cylinder!");
		exit(0);
	}
	cy->radius = d / 2;
	cy->radius2 = cy->radius * cy->radius;
	cy->height = height;
	return (cy);
}

t_material	*material(t_material_type type, double option1)
{
	t_material *mat;

	if (!(mat = (t_material *)malloc(sizeof(t_material))))
		error_malloc();
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

t_texture	*texture(t_tex_type type, t_color3 al1, t_color3 al2, double o1)
{
	t_texture *texture;

	if (!(texture = (t_texture *)malloc(sizeof(t_texture))))
		error_malloc();
	texture->type = type;
	texture->albedo1 = al1;
	texture->albedo2 = al2;
	texture->option1 = o1;
	return (texture);
}

t_texture	*texture_img(t_data *img)
{
	t_texture *texture;

	if (!(texture = (t_texture *)malloc(sizeof(t_texture))))
		error_malloc();
	texture->type = IMAGE;
	texture->albedo1 = color3(0, 0, 0);
	texture->albedo2 = color3(0, 0, 0);
	texture->option1 = 0;
	texture->img = img;
	return (texture);
}
