/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:52:25 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 13:17:04 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool		hit(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	t_bool		hit_anything;
	t_hit_rec	temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while (obj)
	{
		if (hit_obj(obj, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
			rec->obj = obj;
		}
		obj = obj->next;
	}
	return (hit_anything);
}

t_bool		hit_obj(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (obj->type == SP)
		hit_result = hit_sphere(obj, ray, rec);
	else if (obj->type == LIGHT)
		hit_result = (FALSE);
	else if (obj->type == PL)
		hit_result = hit_pl_rotate_check(obj, ray, rec);
	else if (obj->type == SQ)
		hit_result = hit_sq_rotate_check(obj, ray, rec);
	else if (obj->type == CY)
		hit_result = hit_cy_rotate_check(obj, ray, rec);
	else if (obj->type == TR)
		hit_result = hit_triangle(obj, ray, rec);
	else if (obj->type == CB)
		hit_result = hit_cb_rotate_check(obj, ray, rec);
	else if (obj->type == PM)
		hit_result = hit_pm_rotate_check(obj, ray, rec);
	return (hit_result);
}

void		get_record(t_hit_rec *rec, double root, t_objects *obj, t_ray *r)
{
	rec->material = obj->material;
	rec->texture = obj->texture;
	rec->t = root;
	rec->p = ray_at(r, root);
}

void		object2world_rec(t_hit_rec *rec, t_vec3 *offset,
								t_matrix44 *r, t_matrix44 *r_n)
{
	t_matrix44 r_inv;

	r_inv = transpose(r);
	rec->p = mmult_v(rec->p, 0, &r_inv);
	rec->normal = mmult_v(rec->normal, 0, r_n);
	rec->p = vplus(rec->p, *offset);
}
