#include "control.h"

void		cntl_render_start(t_cntl *cntl)
{
	char	*line;

	ft_printf("< Ready for render >\n");
	ft_printf("** Type 'Sample per pixel' **\n:");
	get_next_line(0, &line);
	data_is_integer(line, line);
	cntl->scene->global.sample_per_pixel = ft_atoi(line);
	ft_printf("** Type 'Scatter depth' **\n:");
	get_next_line(0, &line);
	data_is_integer(line, line);
	cntl->scene->global.depth = ft_atoi(line);
	ft_printf("< Start render >\n");
	render(cntl->scene, cntl->img);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	ft_printf("< Finish render >\n");
}




// void		cntl_object(int keycode, t_cntl *cntl)
// {
// 	if (keycode == 7)
// 		cntl_object_translate_x_pos(cntl);
// 	else if (keycode == 9)
// 		cntl_object_translate_y_pos(cntl);
// 	else if (keycode == 126)
// 		cntl_object_scale(cntl);
// 	else if (keycode == 53)
// 		cntl_object_deselect(cntl);
// 	else if (keycode == 15) // key R
// 		cntl_object_rotate(cntl);
// }

// void		cntl_object_select(int button, int x, int y, t_cntl *cntl)
// {
// 	double	u;
// 	double	v;
// 	t_ray	r;
// 	t_hit_record rec;

// 	// printf("button: %d, x:%d, y:%d\n",button, x, y);
// 	if (button != 1)// 좌클릭 아닐 때,
// 		printf("If you want to select object, do left click!\n");
// 	else
// 	{
// 		rec.tmin = 0.0001;
// 		rec.tmax = INFINITY;
// 		u = (double)x / (cntl->scene->canv.width - 1);
// 		v = (double)(cntl->scene->canv.height - y) / (cntl->scene->canv.height - 1);
// 		r.orig = cntl->scene->cam_onair->orig;
// 		r.dir = vunit(vminus(vplus(vplus(cntl->scene->cam_onair->left_bottom, vmult(cntl->scene->cam_onair->horizontal, u)), vmult(cntl->scene->cam_onair->vertical, v)), cntl->scene->cam_onair->orig));
// 		if (hit(cntl->scene->world, &r, &rec))
// 		{
// 			cntl->selected = rec.obj;
// 			cntl->mode = 1;
// 			printf("An object was selected!\n!Deselct key : ESC\n"
// 		}
// 		else
// 		{
// 			cntl->selected = NULL;
// 			printf("There is no object!\n");
// 		}
// 	}
// }

// void		cntl_object_deselect(t_cntl *cntl)
// {
// 	cntl->mode = 0;
// 	cntl->selected = NULL;
// 	printf("< Now default mode >\n");
// }

// int	is_double(char *str)
// {
// 	char *start_point;

// 	start_point = str;
// 	if (*str == '-' || *str == '+')
// 		++str;
// 	while (ft_isdigit(*str))
// 		++str;
// 	if (*str == '.')
// 		++str;
// 	while (ft_isdigit(*str))
// 		++str;
// 	if (*str == 0)
// 		return (0);
// 	ft_printf("Rotation value must be number\n");
// 	ft_printf("** INPUT ERROR **\n");
// 	ft_printf("** your input: \"%s\" **\n", str);
// 	return (-1);
// }

// void		cntl_object_rotate(t_cntl *cntl)
// {
// 	t_objects	*selected;
// 	t_vec3		r_deg;
// 	char		*input;
// 	selected = cntl->selected;
// 	if (selected->type == SP || selected->type == TR)
// 		return ;
// 	if (selected->rotate == NULL)
// 		r_deg = vec3(0,0,0);
// 	else
// 		r_deg = selected->rotate->rotate_deg;
// 	ft_printf("\n*** TYPE Add rotation in degree ***\n");
// 	ft_printf("current_rotate is : (x:%.2f, y:%.2f, z:%.2f)\nx add:\n ", r_deg.x, r_deg.y, r_deg.z);
// 	get_next_line(0, &input);
// 	if(is_double(input) == -1)
// 	{
// 		free(input);
// 		return ;
// 	}
// 	r_deg.x += atod(input);
// 	ft_printf("y add:\n");
// 	free(input);
// 	get_next_line(0, &input);
// 	if(is_double(input) == -1)
// 	{
// 		free(input);
// 		return ;
// 	}
// 	r_deg.y += atod(input);
// 	printf("z add:\n");
// 	free(input);
// 	get_next_line(0, &input);
// 	if(is_double(input) == -1)
// 	{
// 		free(input);
// 		return ;
// 	}
// 	r_deg.z += atod(input);
// 	free(input);
// 	if (selected->rotate != NULL)
// 	{
// 		free(selected->rotate);
// 		free(selected->rotate_normal);
// 	}
// 	selected->rotate = rotate(r_deg);
// 	selected->rotate_normal = rotate_normal(selected->rotate);
// 	ft_printf("Rotation Add success\n");
// 	ft_printf("current_rotate is : (x:%.2f, y:%.2f, z:%.2f)\n", selected->rotate->rotate_deg.x, selected->rotate->rotate_deg.y, selected->rotate->rotate_deg.z);
// 	render_preview(cntl->scene, cntl->img);
// 	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
// }
