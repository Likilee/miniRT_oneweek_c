/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 03:26:16 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 03:27:19 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static t_bool	in_square(t_square *sq, t_point3 *hit_point)
{
	if ((fabs(sq->normal.x) > 0)
		&& (hit_point->y >= sq->min.y && hit_point->y <= sq->max.y)
		&& (hit_point->z >= sq->min.z && hit_point->z <= sq->max.z))
		return (TRUE);
	else if ((fabs(sq->normal.y) > 0)
			&& (hit_point->x >= sq->min.x && hit_point->x <= sq->max.x)
			&& (hit_point->z >= sq->min.z && hit_point->z <= sq->max.z))
		return (TRUE);
	else if ((fabs(sq->normal.z) > 0)
			&& (hit_point->x >= sq->min.x && hit_point->x <= sq->max.x)
			&& (hit_point->y >= sq->min.y && hit_point->y <= sq->max.y))
		return (TRUE);
	return (FALSE);
}

static t_vec3	world2object_sq(t_matrix44 *rotate, t_square *sq, t_ray *r)
{
	t_vec3	offset;

	offset = sq->center;
	r->orig = vminus(r->orig, offset);
	sq->center = vminus(sq->center, offset);
	sq->min = vminus(sq->min, offset);
	sq->max = vminus(sq->max, offset);
	r->orig = mmult_v(r->orig, 1.0, rotate);
	r->dir = mmult_v(r->dir, 0, rotate);
	return (offset);
}

t_bool			hit_sq_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	t_ray			ray_w2o;
	t_square		sq_w2o;
	t_objects		obj_w2o;
	t_bool			hit_result;
	t_vec3			offset;

	if (obj->rotate != NULL)
	{
		obj_w2o = *obj;
		sq_w2o = *(t_square *)obj->element;
		obj_w2o.element = &sq_w2o;
		ray_w2o = *ray;
		offset = world2object_sq(obj->rotate, &sq_w2o, &ray_w2o);
		hit_result = hit_square(&obj_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
	}
	else
		hit_result = hit_square(obj, ray, rec);
	return (hit_result);
}

t_bool			hit_square(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	double		denominator;
	t_vec3		r0_p0;
	t_point3	hit_point;
	double		root;
	t_square	*sq;

	sq = obj->element;
	denominator = vdot(sq->normal, ray->dir);
	if (fabs(denominator) < 0.0001)
		return (FALSE);
	r0_p0 = vminus(sq->center, ray->orig);
	root = vdot(r0_p0, sq->normal) / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);
	hit_point = ray_at(ray, root);
	if (in_square(sq, &hit_point))
	{
		get_record(rec, root, obj, ray);
		rec->normal = sq->normal;
		set_face_normal(ray, rec);
		get_square_uv(rec, sq);
		return (TRUE);
	}
	return (FALSE);
}
