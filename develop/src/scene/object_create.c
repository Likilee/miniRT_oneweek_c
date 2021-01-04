/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:27:12 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:46:57 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere *sp;

	if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		error_malloc();
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_light		*light_point(t_point3 p, t_color3 color, double ka, double bright)
{
	t_light	*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		error_malloc();
	light->type = POINT;
	light->p = p;
	light->light_color = color;
	light->ka = ka;
	light->brightness = bright;
	return (light);
}

t_light		*light_parallel(t_vec3 d, t_color3 color, double ka, double bright)
{
	t_light	*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		error_malloc();
	light->type = PARALLEL;
	light->dir = vmult(vunit(d), -1);
	light->p = point3(0, 0, 0);
	light->ka = ka;
	light->light_color = color;
	light->brightness = bright;
	return (light);
}

t_plane		*plane(t_point3 p, t_vec3 normal)
{
	t_plane *pl;

	if (!(pl = (t_plane *)malloc(sizeof(t_plane))))
		error_malloc();
	pl->p = p;
	pl->normal = normal;
	return (pl);
}
