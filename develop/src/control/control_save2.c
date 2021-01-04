/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_save2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:00:41 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 17:27:26 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		write_bmp(t_data *image, t_scene *scene, int fd)
{
	int		i;

	i = 0;
	while (i < (image->size_line / 4) * scene->canv.height)
	{
		if (i % (image->size_line / 4) < scene->canv.width)
			write(fd, &image->addr[i * 4], 4);
		++i;
	}
}

void		bmp_save_direct(t_cntl *cntl)
{
	t_bmph	bmph;
	t_bool	render_phong;
	char	*line;
	t_data	*image;
	int		fd;

	ft_printf(">> Type rendering mode\n>>: 1 : Phong, 2 : Path trace\n:");
	get_next_line(0, &line);
	if (*line == '1')
		render_phong = TRUE;
	else
		render_phong = FALSE;
	free(line);
	ft_printf(">> Type file name (MUST end with '.bmp'\n:");
	get_next_line(0, &line);
	fd = open(ft_strjoin("./bmp/", line), O_WRONLY | O_CREAT | O_TRUNC, 0666);
	bmph = bmp_get_header(cntl->scene);
	write(fd, &bmph, 54);
	(render_phong == TRUE) ? cntl_save_phong(cntl) : cntl_save_path_trace(cntl);
	image = cntl->img;
	write_bmp(image, cntl->scene, fd);
	ft_printf("[%s] : file has been saved\n", line);
	free(line);
	close(fd);
}

void		cntl_save_phong(t_cntl *cntl)
{
	char	*line;

	ft_printf(">> Ready for PHONG render\n");
	ft_printf(">> Type 'Sample per pixel' for Antialiasing\n:");
	get_next_line(0, &line);
	data_is_integer(line, line);
	cntl->scene->global.spp = ft_atoi(line);
	free(line);
	ft_printf(">> Start render\n");
	render_phong(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	ft_printf(">> Finish render\n");
}

void		cntl_save_path_trace(t_cntl *cntl)
{
	char	*line;

	ft_printf(">> Ready for PATH TRACING render\n");
	ft_printf(">> Type 'Sample per pixel' for Antialiasing\n:");
	get_next_line(0, &line);
	data_is_integer(line, line);
	cntl->scene->global.spp = ft_atoi(line);
	free(line);
	ft_printf(">> Type 'Scatter depth'\n:");
	get_next_line(0, &line);
	data_is_integer(line, line);
	cntl->scene->global.depth = ft_atoi(line);
	free(line);
	ft_printf(">> Start render\n");
	render_path_trace(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	ft_printf(">> Finish render\n");
}
