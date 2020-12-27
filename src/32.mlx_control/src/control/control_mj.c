#include "control.h"

void	get_display_resolution(t_cntl *cntl)
{
	int	x;
	int	y;

	mlx_get_screen_size(cntl->mlx, &x, &y);
	// if (cntl->scene->canv.width > x)
	// 	cntl->scene->canv.width = x;
	// if (cntl->scene->canv.height > y)
	// 	cntl->scene->canv.height = y;
	// dprintf(2, "width : %d", cntl->scene->canv.width);
	// dprintf(2, "height : %d", cntl->scene->canv.height);
	dprintf(2, "width : %d", x);
	dprintf(2, "height : %d", y);
}
