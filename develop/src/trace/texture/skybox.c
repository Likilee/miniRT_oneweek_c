#include "trace.h"


t_color3	albedo_skybox(t_hit_rec *rec)
{
	int			w;
	int			h;
	int			h_inv;
	char		*pixel;
	int			color;
	double		c_scale;
	t_data		*data;
	t_color3	color33;
	int			l;

	data = rec->texture->img;
	l = data->height / 3;
	w = (int)(rec->u * l);
	h = (int)(rec->v * l);
	if (w >= l)
		w = l - 1;
	if (h >= l)
		h = l - 1;
	if (w < 0)
		w = 0;
	if (h < 0)
		h = 0;
	if (rec->normal.x == 1.0) // left
	{
		h += l;
		w = l - w;
	}
	else if (rec->normal.x == -1.0) // right
	{
		h += l;
		w += 2 * l;
	}
	else if (rec->normal.y == 1.0) // down
	{
		w += l;
		h = l - h;
	}
	else if (rec->normal.y == -1.0) // up
	{
		w += l;
		h += 2 * l;
	}
	else if (rec->normal.z == 1.0) // front
	{
		w += l;
		h += l;
	}
	else if (rec->normal.z == -1.0) // back
	{
		w = 4 * l - w;
		h += l;
	}
	c_scale = 1.0 / 255.0;
	h_inv = data->height - h - 1;
	pixel = data->addr + (h_inv * data->size_line + w * (data->bits_per_pixel / 8));
	color = *(int *)pixel;
	color33 = color3(c_scale * get_r(color), c_scale * get_g(color), c_scale * get_b(color));

	return (color33);
}


// t_color3	albedo_skybox(t_hit_rec *rec, t_cube *skybox)
// {
// 	int		w;
// 	int		h;
// 	int		h_inv;
// 	char	*pixel;
// 	int		color;
// 	double	c_scale;
// 	t_data	*data;
// 	int		l;

// 	data = rec->texture->img;
// 	l = data->height / 3;
// 	w = (int)(rec->u * l);
// 	h = (int)(rec->v * l);
// 	if (w < 0)
// 		w = 0;
// 	if (h < 0)
// 		h = 0;
// 	if (rec->normal.x == 1.0) // left
// 	{
// 		h += l;
// 		w = l - w;
// 		if (w >= l)
// 			w = l - 1;
// 		if (h >= 2 * l)
// 			h = 2 * l - 1;
// 	}
// 	else if (rec->normal.x == -1.0) // right
// 	{
// 		h += l;
// 		w += 2 * l;
// 		if (w >= 3 * l)
// 			w = 3 * l - 1;
// 		if (h >= 2 * l)
// 			h = 2 * l - 1;
// 	}
// 	else if (rec->normal.y == 1.0) // down
// 	{
// 		w += l;
// 		if (w >= 2 * l)
// 			w = 2 * l - 1;
// 		if (h >= l)
// 			h = l - 1;
// 	}
// 	else if (rec->normal.y == -1.0) // up
// 	{
// 		w += l;
// 		h += 2 * l;
// 	}
// 	else if (rec->normal.z == 1.0) // front
// 	{
// 		w += l;
// 		h += l;
// 	}
// 	else if (rec->normal.z == -1.0) // back
// 	{
// 		w = 4 * l - w;
// 		h += l;
// 	}
// 	c_scale = 1.0 / 255.0;
// 	if (w >= data->width)
// 		w = data->width - 1;
// 	if (h >= data->height)
// 		h = data->height;
// 	h_inv = data->height - h - 1;
// 	pixel = data->addr + (h_inv * data->size_line + w * (data->bits_per_pixel / 8));
// 	color = *(int *)pixel;
// 	t_color3 color33 = color3(c_scale * get_r(color), c_scale * get_g(color), c_scale * get_b(color));

// 	return (color33);
// }
