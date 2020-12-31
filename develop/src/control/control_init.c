#include "control.h"

void		my_mlx_welcome(t_cntl *cntl)
{
	render_preview(cntl);
	console_msg_welcome();
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
