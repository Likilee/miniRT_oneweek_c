#include "trace.h"

static t_vec3		world2object_pm(t_matrix44 *rotate, t_pyramid *pm, t_ray *ray)
{
	t_vec3	offset;
	int		i;

	offset = pm->center;
	ray->orig = vminus(ray->orig, offset);
	pm->center = vminus(pm->center, offset);
	i  = -1;
	while (++i < 4)
	{
		pm->side[i]->p0 = vminus(pm->side[i]->p0, offset);
		pm->side[i]->p1 = vminus(pm->side[i]->p1, offset);
		pm->side[i]->p2 = vminus(pm->side[i]->p2, offset);
	}
	pm->bottom->center = vminus(pm->bottom->center, offset);
	pm->bottom->min = vminus(pm->bottom->min, offset);
	pm->bottom->max = vminus(pm->bottom->max, offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
	return (offset);
}

static t_bool		object2world_pm(t_pyramid *pm, t_vec3 *offset)
{
	int		i;

	pm->center = vplus(pm->center, *offset);
	i  = -1;
	while (++i < 4)
	{
		pm->side[i]->p0 = vplus(pm->side[i]->p0, *offset);
		pm->side[i]->p1 = vplus(pm->side[i]->p1, *offset);
		pm->side[i]->p2 = vplus(pm->side[i]->p2, *offset);
	}
	pm->bottom->center = vplus(pm->bottom->center, *offset);
	pm->bottom->min = vplus(pm->bottom->min, *offset);
	pm->bottom->max = vplus(pm->bottom->max, *offset);
	return (FALSE);
}

t_bool				hit_pm(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_pyramid		*pm;
	t_objects		container;
	t_hit_record	temp_rec;
	t_bool			hit_pyramid;
	t_ray 			ray_w2o;
	int				i;
	t_vec3			offset;
	pm = obj->element;
	ray_w2o = *ray;
	container.rotate = NULL;
	container.rotate_normal= NULL;
	hit_pyramid = FALSE;
	temp_rec = *rec;
	offset = vec3(0,0,0);
	if (obj->rotate != NULL)
		offset = world2object_pm(obj->rotate, pm, &ray_w2o);
	i = -2;
	while(++i < 4)
	{
		if (i == -1)
		{
			container.element = pm->bottom;
			if (hit_square(&container, &ray_w2o, &temp_rec))
			{
				hit_pyramid = TRUE;
				temp_rec.tmax = temp_rec.t;
				*rec = temp_rec;
			}
		}
		else if (hit_triangle(pm->side[i], &ray_w2o, &temp_rec))
		{
			hit_pyramid = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
	}
	object2world_pm(pm, &offset);
	return (hit_pyramid);
}
