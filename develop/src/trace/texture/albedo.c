/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albedo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:17:31 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 15:25:01 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_color3	albedo_rainbow_normal(t_hit_rec *rec)
{
	t_color3 rainbow;

	rainbow = color3(rec->normal.x + 1.0,
					rec->normal.y + 1.0,
					rec->normal.z + 1.0);
	return (vmult(rainbow, 0.5));
}

t_color3	albedo_image_uv(t_hit_rec *rec)
{
	int		wh[2];
	char	*pixel;
	int		color;
	double	c_scale;
	t_data	*data;

	data = rec->texture->img;
	rec->u = saturate(rec->u);
	rec->v = saturate(rec->v);
	wh[0] = (int)(rec->u * data->width);
	wh[1] = (int)(rec->v * data->height);
	c_scale = 1.0 / 255.0;
	if (wh[0] >= data->width)
		wh[0] = data->width - 1;
	if (wh[1] >= data->height)
		wh[1] = data->height;
	wh[1] = data->height - wh[1] - 1;
	pixel = data->addr + (wh[1] * data->size_line
						+ wh[0] * (data->bits_per_pixel / 8));
	color = *(int *)pixel;
	return (color3(c_scale * get_r(color),
					c_scale * get_g(color),
					c_scale * get_b(color)));
}
