#include  "control.h"

void		my_mlx_control(t_cntl *cntl)
{
	mlx_hook(cntl->win, X_EVENT_KEY_PRESS, (1L<<0), cntl_key_press, cntl); // 키입력 확인(안에서 분기)
	mlx_hook(cntl->win, X_EVENT_KEY_EXIT, (1L<<5), cntl_close, cntl); // 엑스 누르면 종료,
	mlx_hook(cntl->win, X_EVENT_MOUSE, (1L<<6), cntl_mouse_click, cntl); // 오브젝트 선택
	mlx_loop(cntl->mlx);
}

int			cntl_key_press(int keycode, t_cntl *cntl)
{
	if (cntl->mode == SAVM)
		cntl_save(cntl, keycode);
	else if (keycode == KEY_SP)
		cntl_light_on_and_off(cntl);
	else if (keycode == KEY_F)
		cntl_render_filter_change(cntl);
	else if (keycode == KEY_O && cntl->mode != OBJM)
		cntl_object_mode_on(cntl);
	else if (keycode == KEY_C && cntl->mode != CAMM) // 카메라 모드로 들어감. 'c'키
		cntl_camera_mode_on(cntl);
	else if (keycode == KEY_L && cntl->mode != LIGM)
		cntl_light_mode_on(cntl);
	else if (keycode == KEY_T && cntl->mode != RENM)
		cntl_render_mode_on(cntl);
	else if (keycode == KEY_ESC && cntl->mode == DEFM)
		cntl_close(cntl);
	else if (cntl->mode == OBJM)
		cntl_object(keycode, cntl);
	else if (cntl->mode == CAMM)
		cntl_camera(cntl, keycode);
	else if (cntl->mode == LIGM)
		cntl_light(cntl, keycode);
	else if (cntl->mode == RENM)
		cntl_render(cntl, keycode);
	else
		printf("!! Undefined keycode : %d\n", keycode);
	return (0);
}

int		cntl_mouse_click(int button, int x, int y, t_cntl *cntl)
{
	if (cntl->mode == OBJM)
		cntl_object_select(button, x, y, cntl);
	if (cntl->mode == CAMM)
		cntl_cam_rotate(button, cntl);
	return (0);
}

int		cntl_close(t_cntl *cntl)
{
    printf(">> Close Ray TRACER, Bye Bye~~\n");
	// mlx_destroy_window(cntl->mlx, cntl->win);
	exit(0);
}
