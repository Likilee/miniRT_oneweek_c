#include  "control.h"

int         cntl_close(t_cntl *cntl)
{
    printf("Close mlx, BYE\n");
	mlx_destroy_window(cntl->mlx, cntl->win);
	exit(0);
}

int			cntl_key_press(int keycode, t_cntl *cntl)
{
	if (keycode == 53)
		cntl_close(cntl);
	else if (keycode == 1)
		printf("press key code:%d\n", keycode);
	return (1);
}

int			cntl_key_release(int keycode, t_cntl *cntl)
{
	if (keycode == 53)
		cntl_close(cntl);
	else
		printf("release key code:%d\n", keycode);
	return (1);
}

int			cntl_pointer_move(int  x, int y, t_cntl *cntl)
{
	printf("pointercode:%d, %d\n", x, y);
	return (0);
}

int			cntl_button_press(int  pointer, t_cntl *cntl)
{
	printf("button code:%d\n", pointer);
	return (0);
}

int			cntl_focus_io(int focus, t_cntl *cntl)
{
	printf("focus:%d\n", focus);
	exit(0);
}

// int			my_main_loop()
// {

// }

int			cntl_window_resize(int resize, t_cntl *cntl)
{
	printf("resize:%d\n ",resize);
	return (0);
}

void		my_mlx_control(t_cntl *cntl)
{
	mlx_hook(cntl->win, 2, (1L<<0), cntl_key_press, cntl);
	mlx_hook(cntl->win, 3, (1L<<1), cntl_key_release, cntl);
	mlx_hook(cntl->win, 6, (1L<<6), cntl_pointer_move, cntl);
	mlx_hook(cntl->win, 4, (1L<<4), cntl_button_press, cntl);
	mlx_hook(cntl->win, 5, (1L<<0), cntl_button_press, cntl);
	mlx_hook(cntl->win, 5, (1L<<0), cntl_button_press, cntl);
	mlx_hook(cntl->win, 9, (1L<<21), cntl_focus_io, cntl);
	mlx_hook(cntl->win, 17, (1L<<5), cntl_focus_io, cntl);
	mlx_hook(cntl->win, 25, (1L<<18), cntl_window_resize, cntl);
	// mlx_loop_hook(cntl->mlx, my_main_loop, cntl);
	mlx_loop(cntl->mlx);
}
