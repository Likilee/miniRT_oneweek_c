/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:39:52 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 12:56:00 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

/*
** 이건 스크래치픽셀스 방식으로https://www.scratchapixel.com/lessons/3d-basic-rendering
** ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
*/

t_bool	hit_triangle(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
	t_triangle	*tr;
	t_tr_set	s;

	tr = obj->element;
	s.denominator = vdot(tr->normal, ray->dir);
	if (fabs(s.denominator) < 0.00001)
		return (FALSE);
	s.r0_p0 = vminus(tr->p0, ray->orig);
	s.t = vdot(s.r0_p0, tr->normal) / s.denominator;
	if (s.t < rec->tmin || s.t > rec->tmax)
		return (FALSE);
	s.p = ray_at(ray, s.t);
	s.vp = vminus(s.p, tr->p0);
	s.c0 = vcross(tr->p0p1, s.vp);
	s.vp = vminus(s.p, tr->p1);
	s.c1 = vcross(tr->p1p2, s.vp);
	s.vp = vminus(s.p, tr->p2);
	s.c2 = vcross(tr->p2p0, s.vp);
	if (vdot(s.c0, s.c2) < 0 || vdot(s.c0, s.c1) < 0 || vdot(s.c1, s.c2) < 0)
		return (FALSE);
	get_record(rec, s.t, obj, ray);
	rec->normal = vunit(tr->normal);
	set_face_normal(ray, rec);
	return (TRUE);
}
