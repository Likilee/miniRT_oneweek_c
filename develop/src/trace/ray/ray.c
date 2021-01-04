/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:51:57 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 13:55:51 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_ray		ray(t_point3 orig, t_vec3 dir)
{
	t_ray	new;

	new.orig = orig;
	new.dir = dir;
	return (new);
}

t_point3	ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_color3	ray_color_phong(t_ray *r, t_scene *s)
{
	t_hit_rec	rec;

	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	if (hit(s->world, r, &rec))
		return (direct_lighting(s->world, r, &rec));
	else
	{
		return (color_background(r, s, &rec));
	}
}

t_color3	ray_color_path_trace(t_ray *r, t_scene *s, int depth)
{
	t_hit_rec	rec;
	t_ray		scattered;
	t_color3	attenuation;

	if (depth < 0)
		return (color3(0, 0, 0));
	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	if (hit(s->world, r, &rec))
	{
		if (scatter(r, &rec, &attenuation, &scattered))
		{
			return (vmult_(ray_color_path_trace(&scattered, s, depth - 1),
							attenuation));
		}
		return (albedo_rainbow_normal(&rec));
	}
	else
		return (color_background(r, s, &rec));
}

t_color3	ray_color_preview(t_ray *r, t_scene *s, int light_on)
{
	t_hit_rec	rec;

	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	if (hit(s->world, r, &rec))
	{
		if (light_on == 0)
			return (direct_lighting(s->world, r, &rec));
		else
			return (rec.texture->albedo1);
	}
	else if (light_on == 0)
		return (color_background(r, s, &rec));
	else
		return (color3(0.5, 0.7, 1.0));
}
