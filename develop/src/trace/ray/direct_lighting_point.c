/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_lighting_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:40:26 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 16:49:52 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static void	l_set_init(t_l_set *l)
{
	l->ks = 0.3;
	l->attenuation_radius = 100;
}

t_color3	direct_lighting_point(t_objects *objs, t_light *light,
										t_ray *r, t_hit_rec *rec)
{
	t_l_set		l;

	l.light_dir = vminus(light->p, rec->p);
	l.light_len = vlength(l.light_dir);
	l.light_ray.orig = vplus(rec->p, vmult(rec->normal, 0.0001));
	l.light_ray.dir = l.light_dir;
	if (in_shadow(objs, l.light_ray, l.light_len))
		return (color3(0, 0, 0));
	l.light_len = vlength(l.light_dir);
	l.light_dir = vunit(l.light_dir);
	l.view_dir = vunit(vmult(r->dir, -1));
	l.reflect_dir = reflect(vmult(l.light_dir, -1), rec->normal);
	l_set_init(&l);
	l.kd = fmax(vdot(rec->normal, l.light_dir), 0.0);
	l.ksn = rec->material->option1;
	l.ambient = vmult(light->light_color, light->ka);
	l.diffuse = vmult(light->light_color, l.kd);
	l.spec = pow(fmax(vdot(l.view_dir, l.reflect_dir), 0.0), l.ksn);
	l.specular = vmult(vmult(light->light_color, l.kd), l.spec);
	l.lightintensity = vplus(vplus(l.ambient, l.diffuse), l.specular);
	l.lightradiusmask = pow(saturate(1 - pow((pow(l.light_len, 2)
							/ pow(l.attenuation_radius, 2)), 2)), 2);
	l.distanceattenuation = 1 / (pow((l.light_len), 2) + 1);
	l.lightattenuation = l.distanceattenuation * l.lightradiusmask;
	return (vmult(l.lightintensity, l.lightattenuation));
}
