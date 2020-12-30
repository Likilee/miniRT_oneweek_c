#include "trace.h"

t_bool		hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	//판별식
	double	discriminant;
	double	sqrtd;
	double	root;
	
	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;
	// 판별식이 0보다 작을 때 : 실근 없을 때,
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	// dprintf(2,"ray->dir:%f,%f,%f\n",ray->dir.x, ray->dir.y, ray->dir.z);
	rec->p = ray_at(ray, root);
	// dprintf(2,"rec->p:%f,%f,%f\n",rec->p.x, rec->p.y, rec->p.z);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
	get_sphere_uv(rec);
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 확인해서 저장.
	// dprintf(2,"normal:%f,%f,%f\n",rec->normal.x, rec->normal.y, rec->normal.z);
	rec->material = sp->material;
	rec->texture = sp->texture;
	return (TRUE);
}
