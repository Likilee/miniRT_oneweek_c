#include "trace.h"

// 축정렬된 사각형이라고 생각하고.
// [minx, maxx] , [miny, maxy], [minz], [maxz] 구해서 교점 p 가 해당 범위에 있는지 확인
static t_bool		in_square(t_square *sq, t_point3 *hit_point)
{
	if ((fabs(sq->normal.x) > 0)
		&& (hit_point->y >= sq->min.y && hit_point->y <= sq->max.y)
		&& (hit_point->z >= sq->min.z && hit_point->z <= sq->max.z))
		return (TRUE);
	else if ((fabs(sq->normal.y) > 0)
		 	&& (hit_point->x >= sq->min.x && hit_point->x <= sq->max.x)
			&& (hit_point->z >= sq->min.z && hit_point->z <= sq->max.z))
				return (TRUE);
	else if ((fabs(sq->normal.z) > 0)
			&& (hit_point->x >= sq->min.x && hit_point->x <= sq->max.x)
			&& (hit_point->y >= sq->min.y && hit_point->y <= sq->max.y))
				return (TRUE);
	return (FALSE);
}

static t_vec3		world2object_sq(t_matrix44 *rotate, t_square *sq, t_ray *ray)
{
	t_vec3	offset;

	offset = sq->center;
	ray->orig = vminus(ray->orig, offset);
	sq->center = vminus(sq->center, offset);
	sq->min =  vminus(sq->min, offset);
	sq->max = vminus(sq->max, offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
	return (offset);
}

t_bool		hit_sq_rotate_check(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_ray			ray_w2o;
	t_square 		sq_w2o;
	t_objects		obj_w2o;
	t_bool			hit_result;
	t_vec3			offset;

	if (obj->rotate != NULL)
	{
		obj_w2o = *obj;
		sq_w2o = *(t_square *)obj->element;
		obj_w2o.element = &sq_w2o;
		ray_w2o = *ray;
		offset = world2object_sq(obj->rotate, &sq_w2o, &ray_w2o);
		hit_result = hit_square(&obj_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
	}
	else
		hit_result = hit_square(obj, ray, rec);
	return (hit_result);
}

t_bool		hit_square(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	double		denominator;
	t_vec3		r0_p0; // ray origin to plane point p
	t_point3	hit_point;
	double		root;
	t_point3	min;
	t_point3	max;
	t_square	*sq;

	sq = obj->element;
	denominator = vdot(sq->normal, ray->dir);
	if (fabs(denominator) < 0.0001) // 분모가 거의 0이면! = 평면과 직선은 평행
		return (FALSE);
	r0_p0 = vminus(sq->center, ray->orig);
	root = vdot(r0_p0, sq->normal) / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);
	hit_point = ray_at(ray, root);
	if (in_square(sq, &hit_point))
	{
		rec->t = root;
		rec->p = hit_point;
		rec->normal = sq->normal;
		set_face_normal(ray, rec);
		rec->material = obj->material;
		rec->texture = obj->texture;
		return (TRUE);
	}
	return (FALSE);
}
