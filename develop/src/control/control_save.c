#include "control.h"

void		cntl_save(t_cntl *cntl, int	keycode)
{
	printf(">> Do you want to save RENDERED img? \n>> (presss y or n)\n");
	if (keycode == KEY_Y)
	{
		bmp_save(cntl->scene);
		cntl_default_mode_on(cntl);
	}
	else if (keycode == KEY_N)
		cntl_default_mode_on(cntl);
}
