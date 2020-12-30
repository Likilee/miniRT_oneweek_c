#include "trace.h"
#include <time.h>

typedef struct	s_thread_data
{
	int			lane;
	int			count;
	t_scene		*s;
}				t_thread_data;

void	*render_mult(void *thread_data)
{
	t_thread_data	t;
	int				j;
	int				i;
	int				k;
	double			u;
	double			v;
	t_ray			r;
	t_color3		pixel_color;

	t = *(t_thread_data *)thread_data;
	i = t.s->canv.height - 1 - t.lane;
	while (i >= 0)
	{
		j = -1;
		while (++j < t.s->canv.width)
		{
			pixel_color = color3(0, 0, 0);
			k = 0;
			while (k++ < t.s->global.sample_per_pixel)
			{
				u = (double)(i + random_jitter(t.s->global.sample_per_pixel, k)) / (t.s->canv.width - 1);
				v = (double)(j + random_jitter(t.s->global.sample_per_pixel, k)) / (t.s->canv.height - 1);
				//ray from camera origin to pixel
				r.orig = t.s->cam_onair->orig;
				// left_bottom + u * horizontal + v * vertical - origin
				r.dir = vunit(vminus(vplus(vplus(t.s->cam_onair->left_bottom, vmult(t.s->cam_onair->horizontal, u)), vmult(t.s->cam_onair->vertical, v)), t.s->cam_onair->orig));
				pixel_color = vplus(pixel_color, ray_color(&r, t.s->world, &t.s->global, t.s->global.depth));
			}
			pixel_color = vdivide(pixel_color, t.s->global.sample_per_pixel);
			pixel_color = vmin(vplus(pixel_color, t.s->global.ambient), color3(1,1,1)); // sum global_ambient + ray_color;
			my_mlx_pixel_put(t.s->img, i, t.s->canv.height - j - 1, create_rgb(&pixel_color));
		}
		i -= t.count;
	}
	return (NULL);
}
# define COUNT 20

void	render(t_scene *scene, t_data *img)
{
	pthread_t		p_thread[COUNT];
	t_thread_data	data[COUNT];
	int				i;
	int				thr_id;
	clock_t			start, end;
	double			result;

	i = -1;
	while (++i < COUNT)
	{
		data[i].count = COUNT;
		data[i].s = scene;
	}
	i = -1;
	while (++i < COUNT)
	{
		data[i].lane = i;
		thr_id = pthread_create(&p_thread[i], NULL, render_mult, (void *)&data[i]);
		if (thr_id < 0)
		{
			perror("thread create error : ");
			exit(0);
		}
	}
	start = clock();// 시간 측정 시작
	i = -1;
	while (++i < COUNT)
		pthread_join(p_thread[i], NULL);
	end = clock(); // 시간 측정  끝!;
	result = (double)(end - start);
	dprintf(2, "프로그램 동작 시간:%f\n", result / CLOCKS_PER_SEC / COUNT);
}

void	render_preview(t_scene *scene, t_data *img, int light_on)
{
	int	i;
	int	j;
	int	k;
	double u;
	double v;
	t_ray	r;

	t_color3	pixel_color;
	j = scene->canv.height;
	while (--j >= 0)
	{
		// dprintf(2, "Printing image :Line remain > %d\n", j);
		i = -1;
		while (++i < scene->canv.width)
		{
			pixel_color = color3(0, 0, 0);
			u = (double)i / (scene->canv.width - 1);
			v = (double)j / (scene->canv.height - 1);
			r.orig = scene->cam_onair->orig;
			r.dir = vunit(vminus(vplus(vplus(scene->cam_onair->left_bottom, vmult(scene->cam_onair->horizontal, u)), vmult(scene->cam_onair->vertical, v)), scene->cam_onair->orig));
			pixel_color = vplus(pixel_color, ray_color_preview(&r, scene->world, &scene->global, light_on));
			pixel_color = vmin(vplus(pixel_color, scene->global.ambient), color3(1,1,1)); // sum global_ambient + ray_color;
			my_mlx_pixel_put(img, i, scene->canv.height - j - 1, create_rgb(&pixel_color));
		}
	}
}
