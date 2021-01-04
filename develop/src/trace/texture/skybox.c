/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:40:00 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 15:41:13 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static int		saturate_w(int w, int l, t_hit_rec *rec)
{
	if (rec->normal.x == 1.0)
		w = l - w;
	else if (rec->normal.x == -1.0)
		w += 2 * l;
	else if (rec->normal.y == 1.0)
		w += l;
	else if (rec->normal.y == -1.0)
		w += l;
	else if (rec->normal.z == 1.0)
		w += l;
	else if (rec->normal.z == -1.0)
		w = 4 * l - w;
	return (w);
}

static int		saturate_h(int h, int l, t_hit_rec *rec)
{
	if (rec->normal.x == 1.0)
		h += l;
	else if (rec->normal.x == -1.0)
		h += l;
	else if (rec->normal.y == 1.0)
		h = l - h;
	else if (rec->normal.y == -1.0)
		h += 2 * l;
	else if (rec->normal.z == 1.0)
		h += l;
	else if (rec->normal.z == -1.0)
		h += l;
	return (h);
}

t_color3		albedo_skybox(t_hit_rec *rec)
{
	int			wh[2];
	int			color;
	double		c_scale;
	t_data		*data;
	int			l;

	data = rec->texture->img;
	l = data->height / 3;
	wh[0] = (int)(rec->u * l);
	wh[1] = (int)(rec->v * l);
	saturate_min_max_int(wh[0], 0, l - 1);
	saturate_min_max_int(wh[1], 0, l - 1);
	wh[0] = saturate_w(wh[0], l, rec);
	wh[1] = saturate_h(wh[1], l, rec);
	c_scale = 1.0 / 255.0;
	wh[1] = data->height - wh[1] - 1;
	color = *(int *)(data->addr + (wh[1] * data->size_line
								+ wh[0] * (data->bits_per_pixel / 8)));
	return (color3(c_scale * get_r(color),
					c_scale * get_g(color),
					c_scale * get_b(color)));
}

t_color3		color_background(t_ray *r, t_scene *s, t_hit_rec *rec)
{
	double			t;

	if (s->background == NULL)
	{
		t = 0.5 * (r->dir.y + 1);
		return (vplus(vmult(color3(1, 1, 1), 1.0 - t),
				vmult(color3(0.5, 0.7, 1.0), t)));
	}
	else if (hit_cube(s->background, r, rec))
		return (albedo_skybox(rec));
	else
		return (color3(0.2, 0.3, 0.4));
}
