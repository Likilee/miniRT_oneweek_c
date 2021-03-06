/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_preview.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:00:05 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 14:10:47 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static void	pixel_put_preview(t_scene *s, t_ray *r, int *i, t_bool light_on)
{
	double			uv[2];
	t_color3		pixel_color;

	pixel_color = color3(0, 0, 0);
	uv[0] = (double)i[0] / (s->canv.height - 1);
	uv[1] = (double)i[1] / (s->canv.width - 1);
	r->orig = s->cam_onair->orig;
	r->dir = vunit(vminus(vplus(vplus(s->cam_onair->left_bottom,
				vmult(s->cam_onair->horizontal, uv[1])),
				vmult(s->cam_onair->vertical, uv[0])), s->cam_onair->orig));
	pixel_color = vplus(pixel_color, ray_color_preview(r, s, light_on));
	pixel_color = vplus(pixel_color, s->global.ambient);
	filter(&pixel_color, &s->global);
	my_mlx_pixel_put(s->img, i[1], s->canv.height - i[0] - 1,
									create_rgb(&pixel_color));
}

static void	*render_preview_thread(void *thread_data)
{
	t_pth_data		t;
	t_scene			*s;
	int				i[2];
	t_ray			r;

	t = *(t_pth_data *)thread_data;
	s = t.c->scene;
	i[0] = s->canv.height - 1 - t.lane;
	while (i[0] >= 0)
	{
		i[1] = -1;
		while (++i[1] < s->canv.width)
			pixel_put_preview(s, &r, i, t.c->light_on);
		i[0] -= t.count;
	}
	return (NULL);
}

void		render_preview(t_cntl *cntl)
{
	pthread_t		p_thread[COUNT];
	t_pth_data		data[COUNT];
	int				i;

	i = -1;
	while (++i < COUNT)
	{
		data[i].count = COUNT;
		data[i].c = cntl;
	}
	i = -1;
	while (++i < COUNT)
	{
		data[i].lane = i;
		if (pthread_create(&p_thread[i], NULL, render_preview_thread,
											(void *)&data[i]) < 0)
		{
			perror("thread create error : ");
			exit(0);
		}
	}
	i = -1;
	while (++i < COUNT)
		pthread_join(p_thread[i], NULL);
}
