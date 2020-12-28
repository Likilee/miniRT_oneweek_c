#include "print.h"

t_bmph	bmp_get_header(t_scene *scene)
{
	int		width;
	int		height;
	t_bmph	bmph;

	// width = scene->img->line_length / 4;
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

	ft_printf("Type save file name (MUST end with '.bmp'\n:");
	get_next_line(0, &file_name);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	bmph = bmp_get_header(scene);
	write(fd, &bmph, 54);
	image = scene->img;

	int i = 0;
	while (i < (image->line_length / 4) * scene->canv.height)
	{
		if (i % (image->line_length / 4) < scene->canv.width)
			write(fd, &image->addr[i * 4], 4);
			++i;
	}
	// int y;
	// int j;
	// int padding = scene->img->line_length % 4;
	// j = scene->canv.height;
	// while (--j >= 0)
	// {
	// 	y = scene->canv.height - j - 1;
	// 	write(fd, &image->addr[y * image->line_length], bmph.info_h.width * 4);
	// 	y = -1;
	// 	while (++y < padding)
	// 		write(fd, "\x00", 1);
	// }
	// int padding = scene->canv.width - bmph.info_h.width;
	// while (i < -bmph.info_h.height)
	// {
	// 	write(fd, image->addr + i * image->line_length, bmph.info_h.width * 4);
	// 	write(fd, "00000000000000000000000000000000000000000000000000", padding * 4);
	// 	++i;
	// }

	ft_printf("[%s] : file has been saved\n", file_name);
	free(file_name);
	close(fd);
}

/*
	while (--i >= 0)
	{
		j = -1;
		while (++j < game->img->width)
			write(fd, &game->data[i * game->img->width + j], 3);
		j = -1;
		while (++j < padding)
			write(fd, "\x00", 1);
	}
}
*/
