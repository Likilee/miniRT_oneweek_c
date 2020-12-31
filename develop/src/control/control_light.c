#include "control.h"

void	cntl_light(t_cntl *cntl, int keycode)
{
	if (keycode == KEY_TAB) // 광원 바꾸기. 오른쪽 방향키
		cntl_light_select(cntl);
	else if (keycode == KEY_Q || keycode == KEY_A || keycode == KEY_E
			|| keycode == KEY_W || keycode == KEY_S || keycode == KEY_D)
		cntl_light_translate(cntl, keycode);
	else if (keycode == KEY_ESC) // 선택 종료 esc
	{
		cntl->selected = NULL;
		cntl_default_mode_on(cntl);
	}
	else if (keycode == KEY_AR_U) // 밝기 밝게 =
		cntl_light_bright_up(cntl);
	else if (keycode == KEY_AR_D) // 밝기 어둡게 -
		cntl_light_bright_down(cntl);
	render_preview(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_light_mode_on(t_cntl *cntl)
{
	t_objects	*temp;

	cntl->mode = LIGM;
	temp = cntl->scene->world;
	if (cntl->selected == 0)
	{
		while (temp->type != LIGHT)
			temp = temp->next;
		cntl->selected = temp;
	}
	console_msg_light_mode();
}

void	cntl_light_on_and_off(t_cntl *cntl)
{
	if (cntl->light_on == LIGHT_OFF)
	{
		cntl->light_on = LIGHT_ON;
		ft_printf(">> Light ON\n");
	}
	else
	{
		cntl->light_on = LIGHT_OFF;
		ft_printf(">> Light OFF\n");
	}
	render_preview(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_light_select(t_cntl *cntl)
{
	t_objects	*temp;

	if (cntl->selected == NULL  || cntl->selected->next == NULL)
		temp = (t_objects *)cntl->scene->world;
	else
		temp = (t_objects *)cntl->selected->next;
	while (temp && temp->type != LIGHT)
		temp = temp->next;
	if (temp == NULL)
	{
		temp = (t_objects *)cntl->scene->world;
		while (temp && temp->type != LIGHT)
			temp = temp->next;
		cntl->selected = temp;
		printf(">> Last light\n");
	}
	else
	{
		cntl->selected = temp;
		printf(">> Next light\n");
	}
}

void	cntl_light_bright_up(t_cntl *cntl)
{
	double		brightness;
	t_color3	*light_color;
	t_light		*light;

	light = ((t_light *)(cntl->selected->element));

	brightness = light->brightness;
	light_color = &light->light_color;
	if (cntl->selected->type == LIGHT)
	{
		light->brightness += 0.1;
		if (light->brightness > 1)
			light->brightness = 1;
		*light_color = vdivide(*light_color, brightness);
		brightness = light->brightness;
		*light_color = vmult(*light_color, brightness);
	}
	printf(">> Increased brightness : (%f,%f,%f)\n", light_color->x, light_color->y, light_color->z);
}

void	cntl_light_bright_down(t_cntl *cntl)
{
	double		brightness;
	t_color3	*light_color;

	brightness = ((t_light *)(cntl->selected->element))->brightness;
	light_color = &((t_light *)(cntl->selected->element))->light_color;
	if (cntl->selected->type == LIGHT)
	{
		((t_light *)(cntl->selected->element))->brightness -= 0.1;
		if (((t_light *)(cntl->selected->element))->brightness <= 0)
			((t_light *)(cntl->selected->element))->brightness = 0.000001;
		*light_color = vdivide(*light_color, brightness);
		brightness = ((t_light *)(cntl->selected->element))->brightness;
		*light_color = vmult(*light_color, brightness);
	}
	printf(">> Decreased brightness : (%f,%f,%f)\n", light_color->x, light_color->y, light_color->z);
}

void		cntl_light_translate(t_cntl *cntl, int keycode)
{
	t_vec3	move;
	t_light *l;

	l = cntl->selected->element;
	if (keycode == KEY_Q)
		move = vec3(1, 0, 0);
	else if (keycode == KEY_A)
		move = vec3(-1, 0, 0);
	else if (keycode == KEY_W)
		move = vec3(0, 1, 0);
	else if (keycode == KEY_S)
		move = vec3(0, -1, 0);
	else if (keycode == KEY_E)
		move = vec3(0, 0, 1);
	else
		move = vec3(0, 0, -1);
	l->p = vplus(l->p, move);
}
