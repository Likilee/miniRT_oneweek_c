#include "trace.h"

void	render(t_scene *scene, t_data *img)
{
	int	i;
	int	j;
	int	k;
	double u;
	double v;
	t_ray	r;

	t_color3	pixel_color;
	// printf("scene->canv.height %d\n", scene->canv.height);
	j = scene->canv.height;
	while (--j >= 0)
	{
		dprintf(2, "Printing image :Line remain > %d\n", j);
		i = -1;
		while (++i < scene->canv.width)
		{
			pixel_color = color3(0, 0, 0);
			k = 0;
			while (k++ < scene->global.sample_per_pixel)
			{
				u = (double)(i + random_jitter(scene->global.sample_per_pixel, k)) / (scene->canv.width - 1);
				v = (double)(j + random_jitter(scene->global.sample_per_pixel, k)) / (scene->canv.height - 1);
				//ray from camera origin to pixel
				r.orig = scene->cam_onair->orig;
				// left_bottom + u * horizontal + v * vertical - origin
				r.dir = vunit(vminus(vplus(vplus(scene->cam_onair->left_bottom, vmult(scene->cam_onair->horizontal, u)), vmult(scene->cam_onair->vertical, v)), scene->cam_onair->orig));
				// printf("r.orig:%f,%f,%f dir:%f,%f,%f\n",r.orig.x, r.orig.y, r.orig.z, r.dir.x, r.dir.y, r.dir.z);
				// if (i == 464 && j == 311)
				pixel_color = vplus(pixel_color, ray_color(&r, scene->world, &scene->global, scene->global.depth));
			}
			pixel_color = vdivide(pixel_color, scene->global.sample_per_pixel);
			pixel_color = vmin(vplus(pixel_color, scene->global.ambient), color3(1,1,1)); // sum global_ambient + ray_color;
			my_mlx_pixel_put(img, i, scene->canv.height - j, create_rgb(&pixel_color));
		}
	}
}

void	render_preview(t_scene *scene, t_data *img)
{
	int	i;
	int	j;
	int	k;
	double u;
	double v;
	t_ray	r;

	t_color3	pixel_color;
	// printf("scene->canv.height %d\n", scene->canv.height);
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
			pixel_color = vplus(pixel_color, ray_color_preview(&r, scene->world, &scene->global));
			pixel_color = vmin(vplus(pixel_color, scene->global.ambient), color3(1,1,1)); // sum global_ambient + ray_color;
			my_mlx_pixel_put(img, i, scene->canv.height - j, create_rgb(&pixel_color));
		}
	}
}
