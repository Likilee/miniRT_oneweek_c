#include "trace.h"

//이건 스크래치픽셀스 방식으로https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
t_bool hit_triangle(t_objects *obj, t_ray *ray, t_hit_rec *rec)
{
    // compute plane's normal
	t_vec3		p;
	t_vec3		c0;
	t_vec3		c1;
	t_vec3		c2; // vector perpendicular to triangle's plane
	t_vec3		vp;
	t_vec3		r0_p0; // ray origin to plane point p
	t_triangle	*tr;
	double		t;
	double		denominator;

	tr = obj->element;
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
	rec->material = obj->material;
	rec->texture = obj->texture;
    return (TRUE); // this ray hits the triangle
}
