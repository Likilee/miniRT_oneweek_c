#include "trace.h"

static void	*render_thread_path(void *thread_data)
{
	t_pth_data		t;
	t_scene			*s;
	int				i[3];
	double			uv[2];
	t_ray			r;
	t_color3		pixel_color;

	t = *(t_pth_data *)thread_data;
	s = t.c->scene;
	i[0] = s->canv.height - 1 - t.lane;
	while (i[0] >= 0)
	{
		i[1] = -1;
		while (++i[1] < s->canv.width)
		{
			pixel_color = color3(0, 0, 0);
			i[2]= -1;
			while (++i[2] < s->global.spp)
			{
				uv[0] = (double)(i[0] + random_jitter(s->global.spp, i[2])) / (s->canv.height - 1);
				uv[1] = (double)(i[1] + random_jitter(s->global.spp, i[2])) / (s->canv.width - 1);
				r.orig = s->cam_onair->orig;
				r.dir = vunit(vminus(vplus(vplus(s->cam_onair->left_bottom, vmult(s->cam_onair->horizontal, uv[1])), vmult(s->cam_onair->vertical, uv[0])), s->cam_onair->orig));
				pixel_color = vplus(pixel_color, ray_color_path_trace(&r, s, s->global.depth));
			}
			pixel_color = vdivide(pixel_color, s->global.spp);
			pixel_color = vplus(pixel_color, s->global.ambient);
			filter(&pixel_color, &s->global);
			my_mlx_pixel_put(s->img, i[1] , s->canv.height - i[0] - 1, create_rgb(&pixel_color));
		}
		if (i[0] % t.progress == 0)
			write(1, "#", 1);
		i[0] -= t.count;
	}
	return (NULL);
}

void	render_path_trace(t_cntl *cntl)
{
	pthread_t		p_thread[COUNT];
	t_pth_data		data[COUNT];
	int				i;

	ft_printf(">> GOAL    ####################[GOAL]\n>> Current ");
	i = -1;
	while (++i < COUNT)
	{
		data[i].count = COUNT;
		data[i].c = cntl;
		data[i].progress = cntl->scene->canv.height / 20;
	}
	i = -1;
	while (++i < COUNT)
	{
		data[i].lane = i;
		if(pthread_create(&p_thread[i], NULL, render_thread_path, (void *)&data[i]) < 0)
		{
			perror("Error\n: ");
			exit(0);
		}
	}
	i = -1;
	while (++i < COUNT)
		pthread_join(p_thread[i], NULL);
	ft_printf("\n");
}
