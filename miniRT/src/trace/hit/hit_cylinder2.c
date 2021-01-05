/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 03:07:44 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 21:30:07 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

double			hit_disk(t_cylinder *cy, t_ray *ray,
						t_hit_rec *rec, t_bool is_top)
{
	t_point3	p;
	t_point3	p0;
	double		denominator;
	t_vec3		r0_p0;
	double		t;

	if (is_top == TRUE)
		p0 = cy->center_top;
	else
		p0 = cy->center_bottom;
	denominator = vdot(cy->axis, ray->dir);
	if (fabs(denominator) < 0.00001)
		return (INFINITY);
	r0_p0 = vminus(p0, ray->orig);
	t = vdot(r0_p0, cy->axis) / denominator;
	if ((t < rec->tmin || t > rec->tmax))
		return (INFINITY);
	p = ray_at(ray, t);
	if (vlength2(vminus(p, p0)) > cy->radius2)
		return (INFINITY);
	return (t);
}

double			hit_finite_cylinder(t_cylinder *cy, t_ray *ray, t_hit_rec *rec)
{
	double		a;
	double		half_b;
	double		d;
	double		t;
	t_point3	p;

	d = cylinder_get_discriminant(cy, *ray, &half_b, &a);
	if (d < 0)
		return (INFINITY);
	d = sqrt(d);
	t = (-half_b - d) / a;
	p = ray_at(ray, t);
	if (!cylinder_root_check(cy, rec, t, p))
	{
		t = (-half_b + d) / a;
		p = ray_at(ray, t);
		if (!cylinder_root_check(cy, rec, t, p))
			return (INFINITY);
	}
	return (t);
}

t_bool			hit_cylinder(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	double		t;
	double		t_disk_top;
	double		t_disk_bot;
	t_cylinder	*cy;

	cy = obj->element;
	t = hit_finite_cylinder(cy, ray, rec);
	t_disk_top = hit_disk(cy, ray, rec, TRUE);
	t_disk_bot = hit_disk(cy, ray, rec, FALSE);
	if (t == INFINITY && t_disk_top == INFINITY && t_disk_bot == INFINITY)
		return (FALSE);
	if (t == dmin3(t, t_disk_top, t_disk_bot))
		record_cylinder(cy, ray, rec, t);
	else if (t_disk_top < t_disk_bot)
		record_disk(cy, ray, rec, t_disk_top);
	else
	{
		record_disk(cy, ray, rec, t_disk_bot);
		rec->front_face = (rec->front_face == TRUE) ? FALSE : TRUE;
	}
	rec->material = obj->material;
	rec->texture = obj->texture;
	return (TRUE);
}

void			record_disk(t_cylinder *cy, t_ray *r, t_hit_rec *rec, double t)
{
	rec->t = t;
	rec->p = ray_at(r, t);
	rec->normal = cy->axis;
	set_face_normal(r, rec);
	get_disk_uv(rec, cy);
}

void			record_cylinder(t_cylinder *cy, t_ray *ray,
								t_hit_rec *rec, double t)
{
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = cylinder_normal(cy, rec);
	set_face_normal(ray, rec);
	get_cylinder_uv(rec, cy);
}
