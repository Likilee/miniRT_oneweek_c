/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 03:02:30 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 03:05:39 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool		hit_sphere(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	t_sphere	*sp;
	t_sp_set	s;

	sp = (t_sphere *)obj->element;
	s.oc = vminus(ray->orig, sp->center);
	s.a = vlength2(ray->dir);
	s.half_b = vdot(s.oc, ray->dir);
	s.c = vlength2(s.oc) - sp->radius2;
	s.discriminant = s.half_b * s.half_b - s.a * s.c;
	if (s.discriminant < 0)
		return (FALSE);
	s.sqrtd = sqrt(s.discriminant);
	s.root = (-s.half_b - s.sqrtd) / s.a;
	if (s.root < rec->tmin || s.root > rec->tmax)
	{
		s.root = (-s.half_b + s.sqrtd) / s.a;
		if (s.root < rec->tmin || s.root > rec->tmax)
			return (FALSE);
	}
	get_record(rec, s.root, obj, ray);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	get_sphere_uv(rec);
	set_face_normal(ray, rec);
	return (TRUE);
}
