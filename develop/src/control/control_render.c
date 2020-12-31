#include "control.h"

void		cntl_render_mode_on(t_cntl *cntl)
{
	cntl->mode = 4;
	console_msg_render_mode();
}

void		cntl_render(t_cntl *cntl, int keycode)
{
	if (keycode == KEY_NP_1 || keycode == KEY_NUM_1)
		cntl_render_phong(cntl);
	else if (keycode == KEY_NP_2 || keycode == KEY_NUM_2)
		cntl_render_path_trace(cntl);
	else if (keycode == KEY_ESC)
		cntl_default_mode_on(cntl);
	else
		printf("!! Select render mode (1 or 2)\n");
}

void		cntl_render_phong(t_cntl *cntl)
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
	printf(">> Do you want to save RENDERED img? \n>> (presss y or n)\n");
	cntl->mode = SAVM;
}

void		cntl_render_path_trace(t_cntl *cntl)
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
	printf(">> Do you want to save RENDERED img? \n>> (presss y or n)\n");
	cntl->mode = SAVM;
}
