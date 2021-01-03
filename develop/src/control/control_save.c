/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:00:38 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 22:21:01 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		cntl_save(t_cntl *cntl, int keycode)
{
	ft_printf(">> Do you want to save RENDERED img? \n>> (presss y or n)\n");
	if (keycode == KEY_Y)
	{
		bmp_save(cntl->scene);
		cntl_default_mode_on(cntl);
	}
	else if (keycode == KEY_N)
		cntl_default_mode_on(cntl);
}

t_bmph		bmp_get_header(t_scene *scene)
{
	int		width;
	int		height;
	t_bmph	bmph;

	width = scene->canv.width;
	height = scene->canv.height;
	bmph.file_h.magic1 = 'B';
	bmph.file_h.magic2 = 'M';
	bmph.file_h.size = 54 + 4 * width * height;
	bmph.file_h.reserved1 = 0;
	bmph.file_h.reserved2 = 0;
	bmph.file_h.offset = 54;
	bmph.info_h.size = 40;
	bmph.info_h.width = width;
	bmph.info_h.height = -height;
	bmph.info_h.plane = 1;
	bmph.info_h.bit_per_pixel = 32;
	bmph.info_h.compression = 0;
	bmph.info_h.size_image = 4 * width * height;
	bmph.info_h.resolution_x = width;
	bmph.info_h.resolution_y = height;
	bmph.info_h.color_used = 0xffffff;
	bmph.info_h.color_important = 0;
	return (bmph);
}

void		bmp_save(t_scene *scene)
{
	t_bmph	bmph;
	char	*file_name;
	t_data	*image;
	int		fd;

	ft_printf(">> Type save file name (MUST end with '.bmp'\n:");
	get_next_line(0, &file_name);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	bmph = bmp_get_header(scene);
	write(fd, &bmph, 54);
	image = scene->img;
	write_bmp(image, scene, fd);
	ft_printf(">> [%s] : file has been saved\n", file_name);
	free(file_name);
	close(fd);
}
