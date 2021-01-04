/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:20:58 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 21:03:40 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		cntl_light(t_cntl *cntl, int keycode)
{
	if (keycode == KEY_TAB)
		cntl_light_select(cntl);
	else if (keycode == KEY_Q || keycode == KEY_A || keycode == KEY_E
			|| keycode == KEY_W || keycode == KEY_S || keycode == KEY_D)
		cntl_light_translate(cntl, keycode);
	else if (keycode == KEY_ESC)
	{
		cntl->selected = NULL;
		cntl_default_mode_on(cntl);
	}
	else if (keycode == KEY_AR_U)
		cntl_light_bright_up(cntl);
	else if (keycode == KEY_AR_D)
		cntl_light_bright_down(cntl);
	render_preview(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void		cntl_light_mode_on(t_cntl *cntl)
{
	t_objects	*temp;

	cntl->mode = LIGM;
	temp = cntl->scene->world;
	while (temp->type != LIGHT)
		temp = temp->next;
	cntl->selected = temp;
	console_msg_light_mode();
}

void		cntl_light_on_and_off(t_cntl *cntl)
{
	if (cntl->light_on == LIGHT_OFF)
	{
		cntl->light_on = LIGHT_ON;
		ft_printf(">> Light ON\n");
	}
	else
	{
		cntl->light_on = LIGHT_OFF;
		ft_printf(">> Light OFF\n");
	}
	render_preview(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void		cntl_light_select(t_cntl *cntl)
{
	t_objects	*temp;

	if (cntl->selected == NULL || cntl->selected->next == NULL)
		temp = (t_objects *)cntl->scene->world;
	else
		temp = (t_objects *)cntl->selected->next;
	while (temp && temp->type != LIGHT)
		temp = temp->next;
	if (temp == NULL)
	{
		temp = (t_objects *)cntl->scene->world;
		while (temp && temp->type != LIGHT)
			temp = temp->next;
		cntl->selected = temp;
		ft_printf(">> Last light\n");
	}
	else
	{
		cntl->selected = temp;
		ft_printf(">> Next light\n");
	}
}
