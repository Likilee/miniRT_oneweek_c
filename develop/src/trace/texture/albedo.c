#include "trace.h"

t_color3	albedo(t_hit_rec *rec)
{
	if (rec->texture->type == SOLID)
		return (rec->texture->albedo1);
	else if (rec->texture->type == CHECKER)
		return (albedo_checker(rec));
	else if (rec->texture->type == CHECKER_UV)
		return (albedo_checker_uv(rec));
	else if (rec->texture->type == RAINBOW)
		return (albedo_rainbow_normal(rec));
	else if (rec->texture->type == IMAGE)
		return (albedo_image_uv(rec));
	else if (rec->texture->type == WAVE)
		return (albedo_wave(rec));
	return (color3(0,0,0));
}

t_color3	albedo_checker(t_hit_rec *rec)
{
	double sines;
	double density;

	density = rec->texture->option1;
	sines = sin(density * rec->p.x) * sin(density * rec->p.y) * sin(density * rec->p.z);
	if (sines < 0)
		return (rec->texture->albedo1);
	else
		return (rec->texture->albedo2);
}

t_color3	albedo_checker_uv(t_hit_rec *rec)
{
	double sines;
	double density;

	density = rec->texture->option1;
	sines = sin(density * rec->u) * sin(density * rec->v);
	if (sines < 0)
		return (rec->texture->albedo1);
	else
		return (rec->texture->albedo2);
}

t_color3	albedo_wave(t_hit_rec *rec)
{
	t_color3	wave;
	double		disrupt;
	double		interval;

	interval = rec->texture->option1;
	wave = rec->texture->albedo1;
	disrupt = (sin(rec->p.x * interval) + 1) * 0.5;
	wave.x = wave.x * disrupt;
	disrupt = (sin(rec->p.y * interval) + 1) * 0.5;
	wave.y = wave.y * disrupt;
	disrupt = (sin(rec->p.z * interval) + 1) * 0.5;
	wave.z = wave.z * disrupt;
	return (wave);
}

t_color3	albedo_rainbow_normal(t_hit_rec *rec)
{
	t_color3 rainbow;

	rainbow = color3(rec->normal.x +1.0, rec->normal.y + 1.0, rec->normal.z + 1.0);
	return (vmult(rainbow, 0.5));
}

t_color3	albedo_image_uv(t_hit_rec *rec)
{
	int		w;
	int		h;
	int		h_inv;
	char	*pixel;
	int		color;
	double	c_scale;
	t_data	*data;

	data = rec->texture->img;
	rec->u = saturate(rec->u);
	rec->v = saturate(rec->v);
	w = (int)(rec->u * data->width);
	h = (int)(rec->v * data->height);
	c_scale = 1.0 / 255.0;
	if (w >= data->width)
		w = data->width - 1;
	if (h >= data->height)
		h = data->height;
	h_inv = data->height - h - 1;
	pixel = data->addr + (h_inv * data->size_line + w * (data->bits_per_pixel / 8));
	color = *(int *)pixel;
	t_color3 color33 = color3(c_scale * get_r(color), c_scale * get_g(color), c_scale * get_b(color));
	return (color33);
}

t_color3	color_background(t_ray *r, t_scene *s, t_hit_rec *rec)
{
	double			t;

	if (s->background == NULL)
	{
		t = 0.5 * (r->dir.y + 1);
		return (vplus(vmult(color3(1, 1, 1), 1.0 - t),
				vmult(color3(0.5, 0.7, 1.0), t)));
	}
	else if (hit_cube(s->background, r, rec))
		return (albedo_skybox(rec));
	else
		return (color3(0.2,0.3,0.4));
}
/* 참고용
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
*/


