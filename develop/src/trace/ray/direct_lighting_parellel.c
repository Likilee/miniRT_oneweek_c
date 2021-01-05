/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_lighting_parellel.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:41:26 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 23:10:17 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_color3	direct_lighting_parallel(t_objects *objs, t_light *light,
											t_ray *r, t_hit_rec *rec)
{
	t_l_set		l;

	l.light_ray.orig = vplus(rec->p, vmult(rec->normal, 0.000001));
	l.light_ray.dir = light->dir;
	if (in_shadow(objs, l.light_ray, INFINITY))
		return (color3(0, 0, 0));
	l.view_dir = vunit(vmult(r->dir, -1));
	l.reflect_dir = reflect(vmult(light->dir, -1), rec->normal);
	l.kd = fmax(vdot(rec->normal, light->dir), 0.0);
	l.ks = 0.5;
	l.ksn = rec->material->option1;
	l.ambient = vmult(light->light_color, light->ka);
	l.diffuse = vmult(light->light_color, l.kd);
	l.spec = pow(fmax(vdot(l.view_dir, l.reflect_dir), 0.0), l.ksn);
	l.specular = vmult(vmult(light->light_color, l.kd), l.spec);
	l.lightintensity = vplus(vplus(l.ambient, l.diffuse), l.specular);
	return (l.lightintensity);
}
