#include "control.h"

void	cntl_camera_hfov(int keycode, t_cntl *cntl)
{
	t_camera	*camera;

	camera = cntl->scene->cam_onair;
	if (keycode == KEY_Q) // q
	{
		camera->hfov += 5;
		if (camera->hfov >= 180)
			camera->hfov = 180;
	}
	else if (keycode == KEY_E) // e
	{
		camera->hfov -= 5;
		if (camera->hfov <= 0)
			camera->hfov = 0;
	}
}

void	cntl_cam_rotate(int button, t_cntl *cntl)
{
	t_matrix44	*cam_rotate;
	t_camera	*cam;

	cam = cntl->scene->cam_onair;
	if (button == M_CLK_L || button == M_SCR_L) // -> 좌클릭
		cam_rotate = rotate(vec3(0,15,0));
	else if (button == M_CLK_R || button == M_SCR_R) // -> 방향키 왼쪽
		cam_rotate = rotate(vec3(0,-15,0));
	else if (button == M_SCR_U) // up
		cam_rotate = rotate(vec3(+15,0,0));
	else if (button == M_SCR_D) // down
		cam_rotate = rotate(vec3(-15,0,0));
	else
	{
		printf(">> Wrong input : button %d\n", button);
		return ;
	}
	cam->dir = mmult_v(cam->dir, 0, cam_rotate);
	free(cam_rotate);
	camera_set(&cntl->scene->canv, cntl->scene->cam_onair);
	render_preview(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}
