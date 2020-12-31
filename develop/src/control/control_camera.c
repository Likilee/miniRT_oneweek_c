#include "control.h"

void	cntl_camera_mode_on(t_cntl *cntl)
{
	system("clear");
	cntl->mode = CAMM;
	console_msg_camera_mode();
}

void	cntl_camera(t_cntl *cntl, int keycode)
{
	if (keycode == KEY_ESC)
	{
		cntl_default_mode_on(cntl);
		return ;
	}
	else if (keycode == KEY_TAB) // 카메라 바꾸기. 오른쪽 방향키
		cntl_camera_select(cntl);
	else if (keycode == KEY_Q || keycode == KEY_E) // 카메라 화각
		cntl_camera_hfov(keycode, cntl);
	else					// 카메라 이동. wasd
		cntl_camera_translate(keycode, cntl);
	camera_set(&cntl->scene->canv, cntl->scene->cam_onair);
	render_preview(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_camera_select(t_cntl *cntl)
{
	t_objects	*temp;

	temp = (t_objects *)cntl->scene->cam_list;
	while (cntl->scene->cam_onair != (t_camera *)temp->element)
		temp = temp->next;
	if (temp->next == 0)
	{
		printf(">> Last Camera\n");
		cntl->scene->cam_onair = (t_camera *)cntl->scene->cam_list->element;
	}
	else
		cntl->scene->cam_onair = ((t_objects *)temp->next)->element;
}

void	cntl_camera_translate(int keycode, t_cntl *cntl)
{
	t_camera	*c;

	c = cntl->scene->cam_onair;
	if (keycode == KEY_W)
		c->orig = vplus(c->orig, vmult(c->dir, 1));
	else if (keycode == KEY_S)
		c->orig = vplus(c->orig, vmult(c->dir, -1));
	else if (keycode == KEY_A)
		c->orig = vplus(c->orig, vcross(vmult(c->dir, -1), c->vertical));
	else if (keycode == KEY_D)
		c->orig = vplus(c->orig, vcross(vmult(c->dir, +1), c->vertical));
}

