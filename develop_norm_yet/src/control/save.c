#include "control.h"

static t_bmph	bmp_get_header(t_scene *scene)
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

void	bmp_save(t_scene *scene)
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

	int i = 0;
	while (i < (image->size_line / 4) * scene->canv.height)
	{
		if (i % (image->size_line / 4) < scene->canv.width)
			write(fd, &image->addr[i * 4], 4);
			++i;
	}
	ft_printf(">> [%s] : file has been saved\n", file_name);
	free(file_name);
	close(fd);
}

void	bmp_save_direct(t_cntl *cntl)
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
	fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	bmph = bmp_get_header(cntl->scene);
	write(fd, &bmph, 54);
	(render_phong == TRUE) ? cntl_save_phong(cntl) : cntl_save_path_trace(cntl);
	image = cntl->img;
	int i = 0;
	while (i < (image->size_line / 4) * cntl->scene->canv.height)
	{
		if (i % (image->size_line / 4) < cntl->scene->canv.width)
			write(fd, &image->addr[i * 4], 4);
			++i;
	}
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
