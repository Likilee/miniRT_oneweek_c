#include "trace.h"

static double	cylinder_get_discriminant(t_cylinder *cy, t_ray *rin, double *half_b, double *a)
{
	t_ray 	r;
	double 	c;
	double 	discriminant;

	//translate ray origin! (trick)
	r = ray(vminus(rin->orig, cy->center_bottom), rin->dir);
	if (cy->axis.x != 0)
	{
		*a = r.dir.y * r.dir.y + r.dir.z * r.dir.z;
		*half_b = r.orig.y * r.dir.y + r.orig.z * r.dir.z;
		c = r.orig.y * r.orig.y + r.orig.z * r.orig.z - cy->radius2;
		discriminant = *half_b * *half_b - *a * c;
	}
	else if (cy->axis.y != 0)
	{
		*a = r.dir.x * r.dir.x + r.dir.z * r.dir.z;
		*half_b = r.orig.x * r.dir.x + r.orig.z * r.dir.z;
		c = r.orig.x * r.orig.x + r.orig.z * r.orig.z - cy->radius2;
		discriminant = *half_b * *half_b - *a * c;
	}
	else
	{
		*a = r.dir.x * r.dir.x + r.dir.y * r.dir.y;
		*half_b = r.orig.x * r.dir.x + r.orig.y * r.dir.y;
		c = r.orig.x * r.orig.x + r.orig.y * r.orig.y - cy->radius2;
		discriminant = *half_b * *half_b - *a * c;
	}
	return (discriminant);
}

static t_bool	cylinder_root_check(t_cylinder *cy, t_hit_record *rec, double root, t_point3 p)
{
	double h;
	double hmin;
	double hmax;

	if (cy->axis.x != 0)
	{
		h = p.x;
		hmin = cy->center_bottom.x;
		hmax = cy->center_top.x;
	}
	else if (cy->axis.y != 0)
	{
		h = p.y;
		hmin = cy->center_bottom.y;
		hmax = cy->center_top.y;
	}
	else
	{
		h = p.z;
		hmin = cy->center_bottom.z;
		hmax = cy->center_top.z;
	}
	if (root < rec->tmin || root > rec->tmax || h < hmin || h > hmax)
		return (FALSE);
	return (TRUE);
}

static t_vec3	cylinder_normal(t_cylinder *cy, t_hit_record *rec)
{
	t_point3 c0;

	if (cy->axis.x != 0)
		c0 = point3(rec->p.x, cy->center_bottom.y, cy->center_bottom.z);
	if (cy->axis.y != 0)
		c0 = point3(cy->center_bottom.x, rec->p.y, cy->center_bottom.z);
	if (cy->axis.z != 0)
		c0 = point3(cy->center_bottom.x, cy->center_bottom.y, rec->p.z);
	return (vunit(vminus(rec->p, c0)));
}

static t_vec3	world2object_cy(t_matrix44 *rotate, t_cylinder *cy, t_ray *ray)
{
	t_vec3	offset;

	offset = cy->center_bottom;
	ray->orig = vminus(ray->orig, cy->center_bottom);
	cy->center_bottom = vminus(cy->center_bottom, offset);
	cy->center_top = vminus(cy->center_top, offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
	return (offset);
}

t_bool		hit_cy_rotate_check(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_ray			ray_w2o;
	t_cylinder 		cy_w2o;
	t_objects		obj_w2o;
	t_bool			hit_result;
	t_vec3			offset;

	if (obj->rotate != NULL)
	{
		obj_w2o = *obj;
		cy_w2o = *(t_cylinder *)obj->element;
		obj_w2o.element = &cy_w2o;
		ray_w2o = *ray;
		offset = world2object_cy(obj->rotate, &cy_w2o, &ray_w2o);
		hit_result = hit_cylinder(&obj_w2o, &ray_w2o, rec);
		object2world_rec(rec, &offset, obj->rotate, obj->rotate_normal);
	}
	else
		hit_result = hit_cylinder(obj, ray, rec);
	return (hit_result);
}

double		hit_disk(t_cylinder *cy, t_ray *ray, t_hit_record *rec, t_bool is_top)
{
	t_point3	p;
	double		denominator;
	t_vec3		r0_p0; // ray origin to plane point p
	double		t;

	if (is_top == TRUE)
		p = cy->center_top;
	else
		p = cy->center_bottom;
	denominator = vdot(cy->axis, ray->dir);
	if (fabs(denominator) < 0.00001) // 분모가 거의 0이면! = 평면과 직선은 평행 또는 평면위에 있음.
		return (INFINITY);
	r0_p0 = vminus(cy->center_top, ray->orig);
	t = vdot(r0_p0, cy->axis) / denominator;
	if ((t < rec->tmin || t > rec->tmax))
		return (INFINITY);
	p = ray_at(ray, t);
	if (vlength2(vminus(p, cy->center_top)) > cy->radius2)
		return (INFINITY);
	return (t);
}

double		hit_finite_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double 		a;
	double 		half_b;
	double 		discriminant;
	double		sqrtd;
	double		t;
	t_point3	p;

	discriminant = cylinder_get_discriminant(cy, ray, &half_b, &a);
	if (discriminant < 0)
		return (INFINITY);
	sqrtd = sqrt(discriminant);
	t = (-half_b - sqrtd) / a;
	p = ray_at(ray, t);
	if (!cylinder_root_check(cy, rec, t, p))
	{
		t = (-half_b + sqrtd) / a;
		p = ray_at(ray, t);
		if (!cylinder_root_check(cy, rec, t, p))
			return (INFINITY);
	}
	return (t);
}
// x,y,z 축방향 실린더로 고정해서 풀어보자(https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
t_bool		hit_cylinder(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	double	t;
	double	t_disk_top;
	double	t_disk_bot;
	t_cylinder *cy;

	cy = obj->element;
	t = hit_finite_cylinder(cy, ray, rec);
	t_disk_top = hit_disk(cy, ray, rec, TRUE);
	t_disk_bot = hit_disk(cy, ray, rec, FALSE);
	if (t == INFINITY && t_disk_top == INFINITY && t_disk_bot == INFINITY)
		return (FALSE);
	if (t == dmin3(t, t_disk_top, t_disk_bot))
		record_cylinder(cy, ray, rec, t);
	else if (t_disk_top < t_disk_bot)
		record_disk(cy, ray, rec, t_disk_top);
	else
	{
		record_disk(cy, ray, rec, t_disk_bot);
		rec->front_face = (rec->front_face == TRUE) ? FALSE : TRUE;
	}
	rec->material = obj->material;
	rec->texture = obj->texture;
	return (TRUE);
}

void		record_disk(t_cylinder *cy, t_ray *ray, t_hit_record *rec, double t)
{
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = cy->axis;
	set_face_normal(ray, rec);
	get_disk_uv(rec, cy);
}

void		record_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec, double t)
{
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = cylinder_normal(cy, rec);
	set_face_normal(ray, rec);
	get_cylinder_uv(rec, cy);
}
