/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_light2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:20:58 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 19:23:02 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		cntl_light_bright_up(t_cntl *cntl)
{
	double		brightness;
	t_color3	*light_color;
	t_light		*light;

	light = ((t_light *)(cntl->selected->element));
	brightness = light->brightness;
	light_color = &light->light_color;
	if (cntl->selected->type == LIGHT)
	{
		light->brightness += 0.1;
		if (light->brightness > 1)
			light->brightness = 1;
		*light_color = vdivide(*light_color, brightness);
		brightness = light->brightness;
		*light_color = vmult(*light_color, brightness);
	}
	ft_printf(">> Increased brightness : (%f,%f,%f)\n",
			light_color->x, light_color->y, light_color->z);
}

void		cntl_light_bright_down(t_cntl *cntl)
{
	double		brightness;
	t_color3	*light_color;

	brightness = ((t_light *)(cntl->selected->element))->brightness;
	light_color = &((t_light *)(cntl->selected->element))->light_color;
	if (cntl->selected->type == LIGHT)
	{
		((t_light *)(cntl->selected->element))->brightness -= 0.1;
		if (((t_light *)(cntl->selected->element))->brightness <= 0)
			((t_light *)(cntl->selected->element))->brightness = 0.000001;
		*light_color = vdivide(*light_color, brightness);
		brightness = ((t_light *)(cntl->selected->element))->brightness;
		*light_color = vmult(*light_color, brightness);
	}
	ft_printf(">> Decreased brightness : (%f,%f,%f)\n",
			light_color->x, light_color->y, light_color->z);
}

void		cntl_light_translate(t_cntl *cntl, int keycode)
{
	t_vec3	move;
	t_light *l;

	l = cntl->selected->element;
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
	l->p = vplus(l->p, move);
}
