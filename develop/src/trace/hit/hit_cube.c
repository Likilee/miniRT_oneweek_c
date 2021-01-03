#include "trace.h"

static void		world2object_cb(t_matrix44 *rotate, t_vec3 *offset, t_ray *ray)
{
	ray->orig = vminus(ray->orig, *offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
}

t_bool		hit_cb_rotate_check(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_ray			ray_w2o;
	t_cube			*cb;
	t_cube			*cb_w2o;
	t_objects		obj_w2o;
	t_bool			hit_result;
	t_vec3			offset;

	if (obj->rotate != NULL)
	{
		obj_w2o = *obj;
		cb = obj->element;
		offset = cb->center;
		cb_w2o = cube(point3(0,0,0), cb->side_len);
		obj_w2o.element = cb_w2o;
		ray_w2o = *ray;
		world2object_cb(obj->rotate, &offset, &ray_w2o);
		hit_result = hit_cube(&obj_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
		free_cube(cb_w2o);
	}
	else
		hit_result = hit_cube(obj, ray, rec);
	return (hit_result);
}

t_bool		hit_cube(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_bool			hit_cube;
	t_cube			*cb;
	t_objects		c;
	int				i;

	hit_cube = FALSE;
	temp_rec = *rec;
	c = *obj;
	cb = obj->element;
	i = -1;
	while(++i < 6)
	{
		c.element = cb->square[i];
		if (hit_square(&c, ray, &temp_rec))
		{
			hit_cube = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
	}
	return (hit_cube);
}
