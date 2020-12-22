#include "trace.h"

//ray 생성자
t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray new;

	new.orig = orig;
	new.dir = dir;
	return (new);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진점.
t_point3 ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_color3	ray_color(t_ray *r, t_objects *objs, t_global *global, int depth)
{
	t_vec3			unit_dir;
	t_vec3			n;
	double			t;
	t_hit_record	rec;
	t_color3		color;
	t_ray			scattered;
	t_color3		attenuation;

	if (depth < 0)
		return (color3(0,0,0));
	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	//광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면!)
	color = color3(0.0, 0.0, 0.0);
	if (hit(objs, r, &rec))
	{
		// 빛을 찾아서어어~!
		if (rec.material->type == DIFFUSE)
			color = vplus(color, direct_lighting(objs, r, &rec, global));
		if (scatter(r, &rec, &attenuation, &scattered))
			return (vplus(color, vmult_(ray_color(&scattered, objs, global, depth -   1), attenuation)));
		return (color3(0,0,0)); // diffuse가 아닐때 기릿~
	}
	else
	{
		//구와 교점이 없으면 하늘로
		unit_dir = vunit(r->dir);
		t = 0.5 * (unit_dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
	}
}
