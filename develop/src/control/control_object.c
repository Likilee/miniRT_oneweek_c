/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:08:00 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 03:04:38 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		cntl_object_mode_on(t_cntl *cntl)
{
	cntl->mode = 1;
	console_msg_object_mode();
}

void		cntl_object(int keycode, t_cntl *cntl)
{
	if (keycode == KEY_ESC && cntl->selected == NULL)
		cntl_default_mode_on(cntl);
	else if (keycode == KEY_ESC && cntl->selected != NULL)
		cntl_object_deselect(cntl);
	else if (keycode == KEY_R)
		cntl_rotate_on_and_off(cntl);
	else if (cntl->selected != NULL)
	{
		if (keycode == KEY_AR_U || keycode == KEY_AR_D)
			cntl_object_scale(cntl, keycode);
		else if (cntl->rotate_on == FALSE &&
			(keycode == KEY_Q || keycode == KEY_A || keycode == KEY_W
			|| keycode == KEY_S || keycode == KEY_E || keycode == KEY_D))
			cntl_object_translate(cntl, keycode);
		else if (cntl->rotate_on == TRUE &&
				(keycode == KEY_Q || keycode == KEY_A || keycode == KEY_W
				|| keycode == KEY_S || keycode == KEY_E || keycode == KEY_D))
			cntl_object_rotate(cntl, keycode);
		render_preview(cntl);
		mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	}
	else
		ft_printf("!! Select object with mouse_l_click first!\n");
}

void		cntl_rotate_on_and_off(t_cntl *cntl)
{
	if (cntl->rotate_on == FALSE)
	{
		cntl->rotate_on = TRUE;
		ft_printf(">> Object rotate mode\n");
	}
	else
	{
		cntl->rotate_on = FALSE;
		ft_printf(">> Object move mode\n");
	}
}

static void	cntl_object_select_set_ray(t_ray *r, t_scene *scene, int x, int y)
{
	double	u;
	double	v;

	u = (double)x / (scene->canv.width - 1);
	v = (double)(scene->canv.height - y) / (scene->canv.height - 1);
	r->orig = scene->cam_onair->orig;
	r->dir = vunit(vminus(vplus(vplus(scene->cam_onair->left_bottom,
			vmult(scene->cam_onair->horizontal, u)),
			vmult(scene->cam_onair->vertical, v)), scene->cam_onair->orig));
}

void		cntl_object_select(int button, int x, int y, t_cntl *cntl)
{
	t_ray			r;
	t_hit_rec	rec;

	if (button != M_CLK_L)
		ft_printf("!! To select object, do left click!\n");
	else
	{
		rec.tmin = 0.0001;
		rec.tmax = INFINITY;
		cntl_object_select_set_ray(&r, cntl->scene, x, y);
		if (hit(cntl->scene->world, &r, &rec))
		{
			cntl->selected = rec.obj;
			cntl->mode = 1;
			ft_printf(">> Object was selected!\n>> Deselct key : ESC\n");
		}
		else
		{
			cntl->selected = NULL;
			ft_printf("!! There is no object :(\n");
		}
	}
}
