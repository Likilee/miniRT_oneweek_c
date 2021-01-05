/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_object_scale.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:20:15 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 19:20:37 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		cntl_object_scale_sp(t_cntl *cntl, double scale)
{
	t_sphere *sp;

	sp = cntl->selected->element;
	sp->radius *= scale;
	sp->radius2 = sp->radius * sp->radius;
}

void		cntl_object_scale_sq(t_cntl *cntl, double scale)
{
	t_square *sq;
	t_square *sq_temp;

	sq = cntl->selected->element;
	sq_temp = square(sq->center, sq->normal, sq->side_len * scale);
	*sq = *sq_temp;
	free(sq_temp);
}

void		cntl_object_scale_cy(t_cntl *cntl, double scale)
{
	t_cylinder *cy;
	t_cylinder *cy_temp;

	cy = cntl->selected->element;
	cy_temp = cylinder(cy->center_bottom, cy->axis,
				cy->radius * 2 * scale, cy->height * scale);
	*cy = *cy_temp;
	free(cy_temp);
}

void		cntl_object_scale_cb(t_cntl *cntl, double scale)
{
	t_cube	*cb;
	t_cube	*cb_temp;
	int		i;

	cb = cntl->selected->element;
	cb_temp = cube(cb->center, cb->side_len * scale);
	i = -1;
	while (++i < 6)
	{
		free(cb->square[i]);
		cb->square[i] = cb_temp->square[i];
	}
	cb->side_len = cb_temp->side_len;
	free(cb_temp);
}

void		cntl_object_scale_pm(t_cntl *cntl, double scale)
{
	t_pyramid	*pm;
	t_pyramid	*pm_temp;
	int			i;
	t_vec3		new_top;

	pm = cntl->selected->element;
	new_top = vminus(pm->top, pm->center);
	new_top.y = new_top.y * scale;
	new_top = vplus(new_top, pm->center);
	pm_temp = pyramid(pm->center, new_top, pm->side_len * scale);
	free(pm->bottom);
	pm->bottom = pm_temp->bottom;
	i = -1;
	while (++i < 4)
	{
		free(pm->side[i]);
		pm->side[i] = pm_temp->side[i];
	}
	pm->side_len = pm_temp->side_len;
	pm->top = new_top;
	free(pm_temp);
}
