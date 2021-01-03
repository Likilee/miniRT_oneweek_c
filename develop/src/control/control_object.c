#include "control.h"

void		cntl_object_mode_on(t_cntl *cntl)
{
	cntl->mode = 1;
	console_msg_object_mode();

}

void		cntl_object(int keycode, t_cntl *cntl)
{
	if (keycode == KEY_ESC && cntl->selected == NULL)
		cntl_default_mode_on(cntl);
	else if (keycode == KEY_ESC && cntl->selected != NULL)
		cntl_object_deselect(cntl);
	else if (keycode == KEY_R)
			cntl_rotate_on_and_off(cntl);
	else if (cntl->selected != NULL)
	{
		if (keycode == KEY_AR_U || keycode == KEY_AR_D)
			cntl_object_scale(cntl, keycode);
		else if (cntl->rotate_on == FALSE &&
			(keycode == KEY_Q || keycode == KEY_A || keycode == KEY_W
			|| keycode == KEY_S || keycode == KEY_E || keycode == KEY_D))
			cntl_object_translate(cntl, keycode);
		else if (cntl->rotate_on == TRUE &&
				(keycode == KEY_Q || keycode == KEY_A || keycode == KEY_W
				|| keycode == KEY_S || keycode == KEY_E || keycode == KEY_D))
			cntl_object_rotate(cntl, keycode);
		render_preview(cntl);
		mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	}
	else
	{
		ft_printf("!! Select object with mouse_l_click first!\n");
		return ;
	}
}

void		cntl_rotate_on_and_off(t_cntl *cntl)
{
	if (cntl->rotate_on == FALSE)
	{
		cntl->rotate_on = TRUE;
		ft_printf(">> Object rotate mode\n");
	}
	else
	{
		cntl->rotate_on = FALSE;
		ft_printf(">> Object move mode\n");
	}
}

void		cntl_object_select(int button, int x, int y, t_cntl *cntl)
{
	double	u;
	double	v;
	t_ray	r;
	t_hit_record rec;

	if (button != M_CLK_L)
		ft_printf("!! To select object, do left click!\n");
	else
	{
		rec.tmin = 0.0001;
		rec.tmax = INFINITY;
		u = (double)x / (cntl->scene->canv.width - 1);
		v = (double)(cntl->scene->canv.height - y) / (cntl->scene->canv.height - 1);
		r.orig = cntl->scene->cam_onair->orig;
		r.dir = vunit(vminus(vplus(vplus(cntl->scene->cam_onair->left_bottom, vmult(cntl->scene->cam_onair->horizontal, u)), vmult(cntl->scene->cam_onair->vertical, v)), cntl->scene->cam_onair->orig));
		if (hit(cntl->scene->world, &r, &rec))
		{
			cntl->selected = rec.obj;
			cntl->mode = 1;
			ft_printf(">> Object was selected!\n>> Deselct key : ESC\n");
		}
		else
		{
			cntl->selected = NULL;
			ft_printf("!! There is no object :(\n");
		}
	}
}

void		cntl_object_deselect(t_cntl *cntl)
{
	cntl->selected = NULL;
	ft_printf(">> Objecr deselected\n");
}

void		cntl_object_rotate(t_cntl *cntl, int keycode)
{
	t_vec3		r_deg;

	if (cntl->selected->type == SP || cntl->selected->type == TR)
		return ;
	r_deg =	(cntl->selected->rotate == NULL) ? vec3(0,0,0) :
			cntl->selected->rotate->rotate_deg;
	if (keycode == KEY_Q)
		r_deg = vplus(r_deg, vec3(15, 0, 0));
	else if (keycode == KEY_A)
		r_deg = vplus(r_deg, vec3(-15, 0, 0));
	else if (keycode == KEY_W)
		r_deg = vplus(r_deg, vec3(0, 15, 0));
	else if (keycode == KEY_S)
		r_deg = vplus(r_deg, vec3(0, -15, 0));
	else if (keycode == KEY_E)
		r_deg = vplus(r_deg, vec3(0, 0, 15));
	else
		r_deg = vec3(0, 0, -15);
	if (cntl->selected->rotate != NULL)
	{
		free(cntl->selected->rotate);
		free(cntl->selected->rotate_normal);
	}
	cntl->selected->rotate = rotate(r_deg);
	cntl->selected->rotate_normal = rotate_normal(cntl->selected->rotate);
}

void		cntl_object_translate(t_cntl *cntl, int keycode)
{
	t_vec3	move;

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
	if (cntl->selected->type == SP)
		cntl_object_translate_sp(cntl, &move);
	else if (cntl->selected->type == PL)
		cntl_object_translate_pl(cntl, &move);
	else if (cntl->selected->type == SQ)
		cntl_object_translate_sq(cntl, &move);
	else if (cntl->selected->type == CY)
		cntl_object_translate_cy(cntl, &move);
	else
		cntl_object_translate2(cntl, &move);
}

void		cntl_object_translate2(t_cntl *cntl, t_vec3 *move)
{
	int		i;

	if (cntl->selected->type == TR)
		cntl_object_translate_tr(cntl, move);
	else if (cntl->selected->type == CB)
		cntl_object_translate_cb(cntl, move);
	else if (cntl->selected->type == PM)
		cntl_object_translate_pm(cntl, move);
}

void		cntl_object_scale(t_cntl *cntl, int keycode)
{
	double		scale;

	scale = (keycode == KEY_AR_U) ? 1.1 : 1.0 / 1.1;
	if (cntl->selected->type == SP)
		cntl_object_scale_sp(cntl, scale);
	else if (cntl->selected->type == SQ)
		cntl_object_scale_sq(cntl, scale);
	else if (cntl->selected->type == CY)
		cntl_object_scale_cy(cntl, scale);
	else if (cntl->selected->type == CB)
		cntl_object_scale_cb(cntl, scale);
	else if (cntl->selected->type == PM)
		cntl_object_scale_pm(cntl, scale);
}
