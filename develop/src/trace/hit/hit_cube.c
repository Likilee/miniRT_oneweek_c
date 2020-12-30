#include "trace.h"

static void		world2object_cb(t_matrix44 *rotate, t_vec3 *offset, t_ray *ray)
{
	ray->orig = vminus(ray->orig, *offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
}

t_bool		hit_cb_rotate_check(t_objects *obj, t_cube *cb, t_ray *ray, t_hit_record *rec)
{
	t_ray			ray_w2o;
	t_cube			*cb_w2o;
	t_bool			hit_result;
	t_vec3			offset;

	if (obj->rotate != NULL)
	{
		cb_w2o = cube(point3(0,0,0), cb->side_len, cb->material, cb->texture);
		offset = cb->center;
		ray_w2o = *ray;
		world2object_cb(obj->rotate, &offset, &ray_w2o);
		hit_result = hit_cube(cb_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
		free_cube(cb_w2o);
	}
	else
		hit_result = hit_cube(cb, ray, rec);
	return (hit_result);
}

t_bool		hit_cube(t_cube *cb, t_ray *ray, t_hit_record *rec)
{
	t_square		*side;
	t_hit_record	temp_rec;
	t_bool			hit_cube;
	int				i;

	i = -1;
	hit_cube = FALSE;
	temp_rec = *rec;
	while(++i < 6)
	{
		side = cb->square[i];
		if (hit_square(side, ray, &temp_rec))
		{
			hit_cube = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
	}
	return (hit_cube);
}
