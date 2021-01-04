/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:42:00 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 13:43:34 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_color3	direct_lighting(t_objects *objs, t_ray *r, t_hit_rec *rec)
{
	t_color3	light_color;
	t_objects	*objs_first;

	light_color = color3(0, 0, 0);
	objs_first = objs;
	while (objs)
	{
		if (objs->type == LIGHT)
			light_color = vplus(light_color, direct_lighting_get(objs_first,
													objs->element, r, rec));
		objs = objs->next;
	}
	return (vmin(vmult_(light_color, albedo(rec)), color3(1, 1, 1)));
}

t_color3	direct_lighting_get(t_objects *objs, t_light *light,
									t_ray *r, t_hit_rec *rec)
{
	if (light->type == POINT)
		return (direct_lighting_point(objs, light, r, rec));
	else if (light->type == PARALLEL)
		return (direct_lighting_parallel(objs, light, r, rec));
	return (color3(0, 0, 0));
}
