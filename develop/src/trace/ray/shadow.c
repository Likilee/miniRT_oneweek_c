/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:58:13 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 13:58:18 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool	in_shadow(t_objects *objs, t_ray light_ray, double light_len)
{
	t_hit_rec rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	light_ray.dir = vunit(light_ray.dir);
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}
