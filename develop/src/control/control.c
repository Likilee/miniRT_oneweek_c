#include  "control.h"

void	cntl_display_resolution(t_cntl *cntl)
{
	int	x;
	int	y;

	mlx_get_screen_size(cntl->mlx, &x, &y);
	if (cntl->scene->canv.width > x)
		cntl->scene->canv.width = x;
	if (cntl->scene->canv.height > y)
		cntl->scene->canv.height = y;
}

int         cntl_close(t_cntl *cntl)
{
	bmp_save(cntl->scene);
    printf("Close mlx, BYE\n");
	// mlx_destroy_window(cntl->mlx, cntl->win);
	exit(0);
}

int		cntl_mouse_click(int button, int x, int y, t_cntl *cntl)
{
	if (cntl->mode == 0)
		cntl_object_select(button, x, y, cntl);
	if (cntl->mode == 2)
		cntl_cam_rotate(button, cntl);
	return (0);

}

int		my_main_loop(t_cntl *cntl)
{
	render_preview(cntl->scene, cntl->img, cntl->light_on);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	return (0);
}

int			cntl_key_press(int keycode, t_cntl *cntl)
{
	if (keycode == 49) // o키 누르면 light on and off
		cntl_light_on_and_off(cntl);
	else if (keycode == 17)
		cntl_render_start(cntl);
	else if (keycode == 8 && cntl->mode != CAMM) // 카메라 모드로 들어감. 'c'키
		cntl_camera_on(cntl);
	else if (keycode == 53 && cntl->mode == DEFM)
		cntl_close(cntl);
	else if (cntl->mode == CAMM)					// 카메라 통제!!!!!!!
		cntl_camera(cntl, keycode);
	else if (cntl->mode == OBJM)
		cntl_object(keycode, cntl);
	else if (keycode == 37 && cntl->mode != LIGM)
		cntl_light_on(cntl);
	else if (cntl->mode == LIGM)
		cntl_light(cntl, keycode);
	else
		printf("press key code:%d\n", keycode);
	return (1);
}

int			cntl_click_x(int focus, t_cntl *cntl)
{
	printf("Goodbye~\n");
	// mlx_destroy_window(cntl->mlx, cntl->win);
	exit(0);
}

void		my_mlx_control(t_cntl *cntl)
{
	//요기 수정
	mlx_hook(cntl->win, 2, (1L<<0), cntl_key_press, cntl); // 키입력 확인(안에서 분기)
	mlx_hook(cntl->win, 17, (1L<<5), cntl_click_x, cntl); // 엑스 누르면 종료,
	mlx_hook(cntl->win, 4, (1L<<6), cntl_mouse_click, cntl); // 오브젝트 선택
	mlx_loop(cntl->mlx);
}
