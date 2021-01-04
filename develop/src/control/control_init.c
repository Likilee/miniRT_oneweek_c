/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:23:37 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 19:24:43 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		my_mlx_welcome(t_cntl *cntl)
{
	render_preview(cntl);
	console_msg_welcome();
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void		cntl_display_resolution(t_cntl *cntl)
{
	int	x;
	int	y;

	mlx_get_screen_size(cntl->mlx, &x, &y);
	if (cntl->scene->canv.width > x)
		cntl->scene->canv.width = x;
	if (cntl->scene->canv.height > y)
		cntl->scene->canv.height = y;
}

void		cntl_init(t_cntl *cntl, char *filepath)
{
	t_data		*image;

	cntl->mlx = mlx_init();
	cntl->scene = read_rt(filepath, cntl->mlx);
	cntl->selected = NULL;
	cntl->mode = 0;
	cntl->light_on = 1;
	cntl->rotate_on = 0;
	cntl_display_resolution(cntl);
	cntl->win = mlx_new_window(cntl->mlx, cntl->scene->canv.width,
				cntl->scene->canv.height, "Kilee's raytracer");
	if (!(image = (t_data *)malloc(sizeof(t_data))))
		error_malloc();
	image->img = mlx_new_image(cntl->mlx,
				cntl->scene->canv.width, cntl->scene->canv.height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
					&image->size_line, &image->endian);
	cntl->img = image;
	cntl->scene->img = image;
	cntl->scene->cam_onair = cntl->scene->cam_list->element;
	camera_set(&cntl->scene->canv, cntl->scene->cam_onair);
}
