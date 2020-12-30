#include "trace.h"

static void		world2object_pm(t_matrix44 *rotate, t_vec3 *offset, t_ray *ray)
{
	ray->orig = vminus(ray->orig, *offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
}

t_bool		hit_pm_rotate_check(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_ray			ray_w2o;
	t_pyramid		*pm_w2o;
	t_pyramid		*pm;
	t_objects		obj_w2o;
	t_bool			hit_result;
	t_vec3			offset;

	if (obj->rotate != NULL)
	{
		obj_w2o = *obj;
		pm = obj->element;
		offset = pm->center;
		pm_w2o = pyramid(point3(0,0,0), vminus(pm->top, offset), pm->side_len);
		obj_w2o.element = pm_w2o;
		ray_w2o = *ray;
		world2object_pm(obj->rotate, &offset, &ray_w2o);
		hit_result = hit_pyramid(&obj_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
		free_pyramid(pm_w2o);
	}
	else
		hit_result = hit_pyramid(obj, ray, rec);
	return (hit_result);
}

t_bool				hit_pyramid(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_bool			hit_pyramid;
	int				i;
	t_objects		c;
	t_pyramid		*pm;

	c = *obj;
	pm = obj->element;
	hit_pyramid = FALSE;
	temp_rec = *rec;
	c.element = pm->bottom;
	if (hit_square(&c, ray, &temp_rec))
	{
		hit_pyramid = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	i = -1;
	while(++i < 4)
	{
		c.element = pm->side[i];
		if (hit_triangle(&c, ray, &temp_rec))
		{
			hit_pyramid = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
	}
	return (hit_pyramid);
}
