#include "trace.h"

static t_vec3		world2object_cb(t_matrix44 *rotate, t_cube *cb, t_ray *ray)
{
	t_vec3	offset;
	int		i;

	offset = cb->center;
	ray->orig = vminus(ray->orig, offset);
	cb->center = vminus(cb->center, offset);
	i  = -1;
	while (++i < 6)
	{
		cb->square[i]->center = vminus(cb->square[i]->center, offset);
		cb->square[i]->min = vminus(cb->square[i]->min, offset);
		cb->square[i]->max = vminus(cb->square[i]->max, offset);
	}
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
	return (offset);
}

static t_bool		object2world_cb(t_cube *cb, t_vec3 *offset)
{
	int		i;

	cb->center = vplus(cb->center, *offset);
	i  = -1;
	while (++i < 6)
	{
		cb->square[i]->center = vplus(cb->square[i]->center, *offset);
		cb->square[i]->min = vplus(cb->square[i]->min, *offset);
		cb->square[i]->max = vplus(cb->square[i]->max, *offset);
	}
	return (FALSE);
}

t_bool		hit_cb(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_cube			*cb;
	t_objects		container;
	t_hit_record	temp_rec;
	t_bool			hit_cube;
	t_ray 			ray_w2o;
	int				i;
	t_vec3			offset;
	cb = obj->element;
	ray_w2o = *ray;
	container.rotate = NULL;
	container.rotate_normal= NULL;
	i = -1;
	hit_cube = FALSE;
	temp_rec = *rec;
	offset = vec3(0,0,0);
	if (obj->rotate != NULL)
		offset = world2object_cb(obj->rotate, cb, &ray_w2o);
	while(++i < 6)
	{
		container.element = cb->square[i];
		if (hit_square(&container, &ray_w2o, &temp_rec))
		{
			hit_cube = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;

		}
	}
	object2world_cb(cb, &offset);
	return (hit_cube);
}
