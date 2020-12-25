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
		hit_result = hit_pl_rotate_check(obj, obj->element, ray, rec);
	else if (obj->type == SQ)
		hit_result = hit_sq_rotate_check(obj, obj->element, ray, rec);
	else if (obj->type == CY)
		hit_result = hit_cy_rotate_check(obj, obj->element, ray, rec);
	else if (obj->type == TR)
		hit_result = hit_triangle(obj->element, ray, rec);
	else if (obj->type == CB)
		hit_result = hit_cb_rotate_check(obj, obj->element, ray, rec);
	else if (obj->type == PM)
		hit_result = hit_pm_rotate_check(obj, obj->element, ray, rec);
	return (hit_result);
}

void		object2world_rec(t_hit_record *rec, t_vec3 *offset, t_matrix44 *r, t_matrix44 *r_n)
{
	t_matrix44 r_inv;

	r_inv = transpose(r);
	rec->p = mmult_v(rec->p, 0, &r_inv);
	rec->normal = mmult_v(rec->normal, 0, r_n);
	rec->p = vplus(rec->p, *offset);
}
