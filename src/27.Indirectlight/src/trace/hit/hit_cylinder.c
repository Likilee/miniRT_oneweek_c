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

static t_vec3	cylinder_normal(t_cylinder *cy, t_vec3 *p)
{
	t_point3 c0;

	if (cy->axis.x != 0)
		c0 = point3(p->x, cy->center_bottom.y, cy->center_bottom.z);
	if (cy->axis.y != 0)
		c0 = point3(cy->center_bottom.x, p->y, cy->center_bottom.z);
	if (cy->axis.z != 0)
		c0 = point3(cy->center_bottom.x, cy->center_bottom.y, p->z);
	return (vunit(vminus(*p, c0)));
}


t_vec3		world2object_cy(t_matrix44 *rotate, t_cylinder *cy, t_ray *ray)
{
	t_vec3	offset;

	offset = cy->center_bottom;
	ray->orig = vminus(ray->orig, offset);
	cy->center_bottom = vminus(cy->center_bottom, offset);
	cy->center_top = vminus(cy->center_top, offset);
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
	return (offset);
}

t_bool		object2world_cy(t_cylinder *cy, t_vec3 *offset)
{
	cy->center_bottom = vplus(cy->center_bottom, *offset);
	cy->center_top = vplus(cy->center_top, *offset);
	return (FALSE);
}

// x,y,z 축방향 실린더로 고정해서 풀어보자(https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
t_bool		hit_cylinder(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy = obj->element;
	double		a;
	double		half_b;
	double		discriminant;
	double		sqrtd;
	double		root;
	t_point3 	p;
	t_vec3 		offset;
	t_ray		ray_w2o;

	ray_w2o = *ray;
	offset = vec3(0,0,0);
	if (obj->rotate != NULL)
		offset = world2object_cy(obj->rotate, cy, &ray_w2o);
	discriminant = cylinder_get_discriminant(cy, &ray_w2o, &half_b, &a);
	if (discriminant < 0)
		return (object2world_cy(cy, &offset));
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	p = ray_at(&ray_w2o, root);
	if (!cylinder_root_check(cy, rec, root, p))
	{
		root = (-half_b + sqrtd) / a;
		p = ray_at(&ray_w2o, root);
		if (!cylinder_root_check(cy, rec, root, p))
			return (object2world_cy(cy, &offset));
	}
	rec->t = root;
	rec->normal = cylinder_normal(cy, &p);
	set_face_normal(ray, rec);
	get_cylinder_uv(rec, cy);
	rec->normal = mmult_v(rec->normal, 0, obj->rotate_normal);
	rec->p = ray_at(ray, root);
	rec->material = cy->material;
	rec->texture = cy->texture;
	// o2w point
	object2world_cy(cy, &offset);
	return (TRUE);
}
