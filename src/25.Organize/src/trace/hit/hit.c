#include "trace.h"

t_bool		hit(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	// temp_rec의 tmin, tmax 값 초기화.
	temp_rec = *rec;
	hit_anything = FALSE;
	while(obj)
	{
		if (hit_obj(obj, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		obj = obj->next;
	}
	return (hit_anything);
}

t_bool		hit_obj(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (obj->type == SP)
		hit_result = hit_sphere(obj->element, ray, rec);
	else if (obj->type == LIGHT)
		hit_result = (FALSE);
	else if (obj->type == PL)
		hit_result = hit_plane(obj->element, ray, rec);
	else if (obj->type == SQ)
		hit_result = hit_square(obj, ray, rec);
	else if (obj->type == CY)
		hit_result = hit_cylinder(obj, ray, rec);
	else if (obj->type == TR)
		hit_result = hit_triangle(obj->element, ray, rec);
	else if (obj->type == CB)
		hit_result = hit_cb(obj, ray, rec);
	else if (obj->type == PM)
		hit_result = hit_pm(obj, ray, rec);
	return (hit_result);
}
