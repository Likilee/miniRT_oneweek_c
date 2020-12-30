#include "trace.h"

t_color3	albedo(t_hit_record *rec)
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
	return (color3(0,0,0));
}

t_color3	albedo_checker(t_hit_record *rec)
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

t_color3	albedo_checker_uv(t_hit_record *rec)
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

t_color3	albedo_rainbow_normal(t_hit_record *rec)
{
	t_color3 rainbow;

	rainbow = color3(rec->normal.x +1.0, rec->normal.y + 1.0, rec->normal.z + 1.0);
	return (vmult(rainbow, 0.5));
}

t_color3	albedo_image_uv(t_hit_record *rec)
{
	int		i;
	int		j;
	int		j_inv;
	char	*pixel;
	int		color;
	double	c_scale;
	t_data	*data;

	data = rec->texture->img;
	rec->u = saturate(rec->u);
	rec->v = saturate(rec->v);
	i = (int)(rec->u * data->width);
	j = (int)(rec->v * data->height);
	c_scale = 1.0 / 255.0;
	if (i >= data->width)
		i = data->width - 1;
	if (j >= data->height)
		j = data->height - 1;
	j_inv = data->height - j;
	pixel = data->addr + (j_inv * data->line_length + i * (data->bits_per_pixel / 8));
	color = *(int *)pixel;
	t_color3 color33 = color3(c_scale * get_r(color), c_scale * get_g(color), c_scale * get_b(color));

	return (color33);
}

/* 참고용
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
*/


