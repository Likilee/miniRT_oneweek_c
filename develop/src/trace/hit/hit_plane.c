/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 03:03:52 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 03:06:07 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static t_vec3	world2object_pl(t_matrix44 *rotate, t_plane *pl, t_ray *ray)
{
	t_vec3	offset;

	offset = pl->p;
	ray->orig = vminus(ray->orig, offset);
	pl->p = vminus(pl->p, offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir = mmult_v(ray->dir, 0, rotate);
	return (offset);
}

t_bool			hit_pl_rotate_check(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	t_ray			ray_w2o;
	t_plane			pl_w2o;
	t_bool			hit_result;
	t_vec3			offset;
	t_objects		obj_w2o;

	if (obj->rotate != NULL)
	{
		obj_w2o = *obj;
		pl_w2o = *(t_plane *)obj->element;
		obj_w2o.element = &pl_w2o;
		ray_w2o = *ray;
		offset = world2object_pl(obj->rotate, &pl_w2o, &ray_w2o);
		hit_result = hit_plane(&obj_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
	}
	else
		hit_result = hit_plane(obj, ray, rec);
	return (hit_result);
}

t_bool			hit_plane(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	t_plane	*pl;
	double	denominator;
	t_vec3	r0_p0;
	double	root;

	pl = obj->element;
	denominator = vdot(pl->normal, ray->dir);
	if (fabs(denominator) < 0.00001)
		return (FALSE);
	r0_p0 = vminus(pl->p, ray->orig);
	root = vdot(r0_p0, pl->normal) / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(pl->normal);
	set_face_normal(ray, rec);
	rec->material = obj->material;
	rec->texture = obj->texture;
	return (TRUE);
}
