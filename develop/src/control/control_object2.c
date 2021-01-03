/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_object2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:08:00 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 22:20:51 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		cntl_object_rotate(t_cntl *cntl, int keycode)
{
	t_vec3		r_deg;

	if (cntl->selected->type == SP || cntl->selected->type == TR)
		return ;
	r_deg = (cntl->selected->rotate == NULL) ? vec3(0, 0, 0) :
			cntl->selected->rotate->rotate_deg;
	if (keycode == KEY_Q)
		r_deg = vplus(r_deg, vec3(15, 0, 0));
	else if (keycode == KEY_A)
		r_deg = vplus(r_deg, vec3(-15, 0, 0));
	else if (keycode == KEY_W)
		r_deg = vplus(r_deg, vec3(0, 15, 0));
	else if (keycode == KEY_S)
		r_deg = vplus(r_deg, vec3(0, -15, 0));
	else if (keycode == KEY_E)
		r_deg = vplus(r_deg, vec3(0, 0, 15));
	else
		r_deg = vec3(0, 0, -15);
	if (cntl->selected->rotate != NULL)
	{
		free(cntl->selected->rotate);
		free(cntl->selected->rotate_normal);
	}
	cntl->selected->rotate = rotate(r_deg);
	cntl->selected->rotate_normal = rotate_normal(cntl->selected->rotate);
}

void		cntl_object_translate(t_cntl *cntl, int keycode)
{
	t_vec3	move;

	if (keycode == KEY_Q)
		move = vec3(1, 0, 0);
	else if (keycode == KEY_A)
		move = vec3(-1, 0, 0);
	else if (keycode == KEY_W)
		move = vec3(0, 1, 0);
	else if (keycode == KEY_S)
		move = vec3(0, -1, 0);
	else if (keycode == KEY_E)
		move = vec3(0, 0, 1);
	else
		move = vec3(0, 0, -1);
	if (cntl->selected->type == SP)
		cntl_object_translate_sp(cntl, &move);
	else if (cntl->selected->type == PL)
		cntl_object_translate_pl(cntl, &move);
	else if (cntl->selected->type == SQ)
		cntl_object_translate_sq(cntl, &move);
	else if (cntl->selected->type == CY)
		cntl_object_translate_cy(cntl, &move);
	else
		cntl_object_translate2(cntl, &move);
}

void		cntl_object_translate2(t_cntl *cntl, t_vec3 *move)
{
	if (cntl->selected->type == TR)
		cntl_object_translate_tr(cntl, move);
	else if (cntl->selected->type == CB)
		cntl_object_translate_cb(cntl, move);
	else if (cntl->selected->type == PM)
		cntl_object_translate_pm(cntl, move);
}

void		cntl_object_scale(t_cntl *cntl, int keycode)
{
	double		scale;

	scale = (keycode == KEY_AR_U) ? 1.1 : 1.0 / 1.1;
	if (cntl->selected->type == SP)
		cntl_object_scale_sp(cntl, scale);
	else if (cntl->selected->type == SQ)
		cntl_object_scale_sq(cntl, scale);
	else if (cntl->selected->type == CY)
		cntl_object_scale_cy(cntl, scale);
	else if (cntl->selected->type == CB)
		cntl_object_scale_cb(cntl, scale);
	else if (cntl->selected->type == PM)
		cntl_object_scale_pm(cntl, scale);
}

void		cntl_object_deselect(t_cntl *cntl)
{
	cntl->selected = NULL;
	ft_printf(">> Object deselected\n");
}
