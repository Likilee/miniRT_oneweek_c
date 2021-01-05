/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_camera2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:33:36 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/05 01:47:14 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_camera_hfov(int keycode, t_cntl *cntl)
{
	t_camera	*camera;

	camera = cntl->scene->cam_onair;
	if (keycode == KEY_Q)
	{
		camera->hfov += 5;
		if (camera->hfov >= 180)
			camera->hfov = 180;
	}
	else if (keycode == KEY_E)
	{
		camera->hfov -= 5;
		if (camera->hfov <= 0)
			camera->hfov = 0;
	}
}

void	cntl_cam_rotate(int button, t_cntl *cntl)
{
	t_matrix44	*cam_rotate;
	t_camera	*cam;

	cam = cntl->scene->cam_onair;
	if (button == M_CLK_L || button == M_SCR_L)
		cam_rotate = rotate(vec3(0, 15, 0));
	else if (button == M_CLK_R || button == M_SCR_R)
		cam_rotate = rotate(vec3(0, -15, 0));
	else if (button == M_SCR_U)
		cam_rotate = rotate(vec3(15, 0, 0));
	else if (button == M_SCR_D)
		cam_rotate = rotate(vec3(-15, 0, 0));
	else
	{
		ft_printf(">> Wrong input : button %d\n", button);
		return ;
	}
	cam->dir = mmult_v(cam->dir, 0, cam_rotate);
	free(cam_rotate);
	camera_set(&cntl->scene->canv, cntl->scene->cam_onair);
	render_preview(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}
