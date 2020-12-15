#include "ray.h"

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
	else if (obj->type == CB)
		hit_result = hit_cb(obj, ray, rec);
	else if (obj->type == CY)
		hit_result = hit_cylinder(obj, ray, rec);
	else if (obj->type == TR)
		hit_result = hit_triangle(obj->element, ray, rec);
	return (hit_result);
}

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

// 평면위의 한점 p0 와 평면과 광선의 교차점 p 를 연결한 벡터와 평면의 법선 벡터의 내적이 0이 되면 p는 평면위에 있다!
// 식1. (p - p0)﹒n
// 식2. rayorigin(r0) + raydir * t = p
// 연립 : t = (p0 - l0)﹒n / l﹒n
t_bool		hit_plane(t_plane *pl, t_ray *ray, t_hit_record *rec)
{
	double	denominator;
	t_vec3	r0_p0; // ray origin to plane point p
	double	root;

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
	rec->material = pl->material;
	rec->texture = pl->texture;
	return (TRUE);
}

// 축정렬된 사각형이라고 생각하고.
// [minx, maxx] , [miny, maxy], [minz], [maxz] 구해서 교점 p 가 해당 범위에 있는지 확인

static t_bool		in_square(t_square *sq, t_point3 *hit_point)
{
	// dprintf(2,"hit_point:%f,%f,%f\n",hit_point->x, hit_point->y, hit_point->z);
	// dprintf(2,"sq->min:%f,%f,%f\n",sq->min.x, sq->min.y, sq->min.z);
	// dprintf(2,"sq->max:%f,%f,%f\n\n",sq->max.x, sq->max.y, sq->max.z);
	if ((sq->normal.x > 0)
		&& (hit_point->y >= sq->min.y && hit_point->y <= sq->max.y)
		&& (hit_point->z >= sq->min.z && hit_point->z <= sq->max.z))
			return (TRUE);
	else if ((sq->normal.y > 0)
		 	&& (hit_point->x >= sq->min.x && hit_point->x <= sq->max.x)
			&& (hit_point->z >= sq->min.z && hit_point->z <= sq->max.z))
				return (TRUE);
	else if ((sq->normal.z > 0)
			&& (hit_point->x >= sq->min.x && hit_point->x <= sq->max.x)
			&& (hit_point->y >= sq->min.y && hit_point->y <= sq->max.y))
				return (TRUE);
	return (FALSE);
}

t_vec3		world2object_sq(t_matrix44 *rotate, t_square *sq, t_ray *ray)
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

t_bool		object2world_sq(t_square *sq, t_vec3 *offset)
{
	sq->center = vplus(sq->center, *offset);
	sq->min =  vplus(sq->min, *offset);
	sq->max = vplus(sq->max, *offset);
	return (FALSE);
}

t_bool		hit_square(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_square *sq;
	double	denominator;
	t_vec3	r0_p0; // ray origin to plane point p
	t_point3	hit_point;
	double	root;
	t_point3 min;
	t_point3 max;
	t_ray ray_w2o;
	t_vec3 offset;

	ray_w2o = *ray;
	sq = obj->element;
	offset = vec3(0,0,0);
	if (obj->rotate != NULL)
		offset = world2object_sq(obj->rotate, sq, &ray_w2o);
	denominator = vdot(sq->normal, ray_w2o.dir);
	if (fabs(denominator) < 0.0001) // 분모가 거의 0이면! = 평면과 직선은 평행
		return (object2world_sq(sq, &offset));
	r0_p0 = vminus(sq->center, ray_w2o.orig);
	root = vdot(r0_p0, sq->normal) / denominator;
	if (root < rec->tmin || root > rec->tmax)
			return (object2world_sq(sq, &offset));
	hit_point = ray_at(&ray_w2o, root);
	if (in_square(sq, &hit_point))
	{
		rec->t = root;
		rec->p = ray_at(ray, root);
		// rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 확인해서 저장.
		rec->normal = mmult_v(sq->normal, 0, obj->rotate_normal);
		set_face_normal(ray, rec);
		rec->material = sq->material;
		rec->texture = sq->texture;
		object2world_sq(sq, &offset);
		return (TRUE);
	}
	return (obj->rotate != NULL) ? (object2world_sq(sq, &offset)) : (FALSE);
}

t_vec3		world2object_cb(t_matrix44 *rotate, t_cube *cb, t_ray *ray)
{
	t_vec3	offset;
	int		i;

	offset = cb->center;
	ray->orig = vminus(ray->orig, offset);
	cb->center = vminus(cb->center, offset);
	i  = -1;
	while (++i < 6)
	{
		cb->square[i]->center = vminus(cb->square[i]->center, offset);
		cb->square[i]->min = vminus(cb->square[i]->min, offset);
		cb->square[i]->max = vminus(cb->square[i]->max, offset);
	}
	ray->orig = mmult_v(ray->orig, 1.0, rotate);
	ray->dir =  mmult_v(ray->dir, 0, rotate);
	return (offset);
}

t_bool		object2world_cb(t_cube *cb, t_vec3 *offset)
{
	int		i;

	i  = -1;
	while (++i < 6)
	{
		cb->square[i]->center = vplus(cb->square[i]->center, *offset);
		cb->square[i]->min = vplus(cb->square[i]->min, *offset);
		cb->square[i]->max = vplus(cb->square[i]->max, *offset);
	}
	return (FALSE);
}

t_bool		hit_cb(t_objects *obj, t_ray *ray, t_hit_record *rec)
{
	t_cube			*cb;
	t_objects		container;
	t_hit_record	temp_rec;
	t_bool			hit_cube;
	t_ray 			ray_w2o;
	int				i;
	t_vec3			offset;

	cb = obj->element;
	ray_w2o = *ray;
	container.rotate = NULL;
	container.rotate_normal= NULL;
	i = -1;
	hit_cube = FALSE;
	temp_rec = *rec;
	offset = vec3(0,0,0);
	if (obj->rotate != NULL)
		offset = world2object_cb(obj->rotate, cb, &ray_w2o);
	while(++i < 6)
	{
		container.element = cb->square[i];
		if (hit_square(&container, ray, &temp_rec))
		{
			hit_cube = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
	}
	object2world_cb(cb, &offset);
	return (hit_cube);
}

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
	ray->orig = vminus(ray->orig, cy->center_bottom);
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

//이건 스크래치픽셀스 방식으로https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
t_bool hit_triangle(t_triangle *tr, t_ray *ray, t_hit_record *rec)
{
    // compute plane's normal
	t_vec3 p;
	t_vec3 c0;
	t_vec3 c1;
	t_vec3 c2; // vector perpendicular to triangle's plane
	t_vec3 vp;
	t_vec3 r0_p0; // ray origin to plane point p

	double t;
	double	denominator;

    // Step 1: finding P - 평면과의 교점 찾기
	denominator = vdot(tr->normal, ray->dir);
	if (fabs(denominator) < 0.000001) // 분모가 거의 0이면! = 평면과 직선은 평행 또는 평면 위에 있음.
		return (FALSE);
	r0_p0 = vminus(tr->p0, ray->orig);
	t = vdot(r0_p0, tr->normal) / denominator;
	if (t < rec->tmin || t > rec->tmax)
		return (FALSE);
    // compute the intersection point using equation 1
    p = vplus(ray->orig, vmult(ray->dir, t));//Vec3f P = orig + t * dir;
    // Step 2: inside-outside test
    // edge 0
	vp = vminus(p, tr->p0);
	c0 = vcross(tr->p0p1, vp);
    // edge 1
	vp = vminus(p, tr->p1);
	c1 = vcross(tr->p1p2, vp);
    // edge 2
	vp = vminus(p, tr->p2);
	c2 = vcross(tr->p2p0, vp);
	if (vdot(c0,c2) < 0 || vdot(c0, c1) < 0 || vdot(c1, c2) < 0)
		return (FALSE);
	rec->t = t;
	rec->p = p;
	rec->normal = vunit(tr->normal);
	set_face_normal(ray, rec);
	rec->material = tr->material;
	rec->texture = tr->texture;
    return (TRUE); // this ray hits the triangle
}
