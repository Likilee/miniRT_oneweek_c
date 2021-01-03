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
t_point3	ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_color3	ray_color_phong(t_ray *r, t_scene *s)
{
	t_hit_rec	rec;

	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	//광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면!)
	if (hit(s->world, r, &rec))
		return (direct_lighting(s->world, r, &rec));
	else
	{
		return (color_background(r, s, &rec));
	}
}

t_color3	ray_color_path_trace(t_ray *r, t_scene *s, int depth)
{
	t_vec3			unit_dir;
	double			t;
	t_hit_rec	rec;
	t_ray			scattered;
	t_color3		attenuation;

	if (depth < 0)
		return (color3(0,0,0));
	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	if (hit(s->world, r, &rec))
	{
		if (scatter(r, &rec, &attenuation, &scattered))
			return (vmult_(ray_color_path_trace(&scattered, s, depth - 1), attenuation));
		return (albedo_rainbow_normal(&rec)); // diffuse이면
	}
	else
	{
		//구와 교점이 없으면 하늘로
		unit_dir = vunit(r->dir);
		t = 0.5 * (unit_dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		return (color_background(r, s, &rec));
	}
}

t_color3	ray_color_preview(t_ray *r, t_scene *s, int light_on)
{
	t_hit_rec	rec;

	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	if (hit(s->world, r, &rec))
	{
		if (light_on == 0)
			return (direct_lighting(s->world, r, &rec));
		else
			return (rec.texture->albedo1);
	}
	else
		return (light_on == 0) ? color_background(r, s, &rec) : (color3(0.5, 0.7, 1.0));		//구와 교점이 없으면 하늘로
}
