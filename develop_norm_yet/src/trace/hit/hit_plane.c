#include "trace.h"

static t_vec3		world2object_pl(t_matrix44 *rotate, t_plane *pl, t_ray *ray)
{
	t_vec3	offset;

	offset = pl->p;
	ray->orig = vminus(ray->orig, offset);
	pl->p = vminus(pl->p, offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
	return (offset);
}

t_bool		hit_pl_rotate_check(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_ray			ray_w2o;
	t_plane 		pl_w2o;
	t_bool			hit_result;
	t_vec3			offset;
	t_objects		obj_w2o;

	if (obj->rotate != NULL)
	{
		obj_w2o = *obj;
		pl_w2o = *(t_plane *)obj->element;
		obj_w2o.element = &pl_w2o;
		ray_w2o = *ray;
		offset = world2object_pl(obj->rotate, &pl_w2o, &ray_w2o);
		hit_result = hit_plane(&obj_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
	}
	else
		hit_result = hit_plane(obj, ray, rec);
	return (hit_result);
}

// 평면위의 한점 p0 와 평면과 광선의 교차점 p 를 연결한 벡터와 평면의 법선 벡터의 내적이 0이 되면 p는 평면위에 있다!
// 식1. (p - p0)﹒n
// 식2. rayorigin(r0) + raydir * t = p
// 연립 : t = (p0 - l0)﹒n / l﹒n
t_bool		hit_plane(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	double	denominator;
	t_vec3	r0_p0; // ray origin to plane point p
	double	root;

	pl = obj->element;
	denominator = vdot(pl->normal, ray->dir);
	if (fabs(denominator) < 0.00001) // 분모가 거의 0이면! = 평면과 직선은 평행 또는 평면위에 있음.
		return (FALSE);
	r0_p0 = vminus(pl->p, ray->orig);
	root = vdot(r0_p0, pl->normal) / denominator;
	if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	// rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 확인해서 저장.
	rec->normal = vunit(pl->normal);
	set_face_normal(ray, rec);
	rec->material = obj->material;
	rec->texture = obj->texture;
	return (TRUE);
}
