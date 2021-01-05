/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_object_translate2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:19:43 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 19:19:50 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		cntl_object_translate_cb(t_cntl *cntl, t_vec3 *move)
{
	t_cube		*cb;
	int			i;

	cb = cntl->selected->element;
	cb->center = vplus(cb->center, *move);
	i = -1;
	while (++i < 6)
	{
		cb->square[i]->center = vplus(cb->square[i]->center, *move);
		cb->square[i]->min = vplus(cb->square[i]->min, *move);
		cb->square[i]->max = vplus(cb->square[i]->max, *move);
	}
}

void		cntl_object_translate_pm(t_cntl *cntl, t_vec3 *move)
{
	t_pyramid	*pm;
	int			i;

	pm = cntl->selected->element;
	pm->center = vplus(pm->center, *move);
	pm->top = vplus(pm->top, *move);
	pm->bottom->center = vplus(pm->bottom->center, *move);
	pm->bottom->min = vplus(pm->bottom->min, *move);
	pm->bottom->max = vplus(pm->bottom->max, *move);
	i = -1;
	while (++i < 4)
	{
		pm->side[i]->p0 = vplus(pm->side[i]->p0, *move);
		pm->side[i]->p1 = vplus(pm->side[i]->p1, *move);
		pm->side[i]->p2 = vplus(pm->side[i]->p2, *move);
	}
}
