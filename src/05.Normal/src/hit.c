#include "structures.h"
#include "utils.h"

double		hit_sphere(t_sphere *sp, t_ray *ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	//판별식
	double	discriminant;

	oc = vminus(ray->orig, sp->center);
	a = vdot(ray->dir, ray->dir);
	b = 2.0 * vdot(oc, ray->dir);
	c = vdot(oc, oc) - sp->radius2;
	discriminant = b * b - 4 * a * c;

	// 판별식이 0보다 작을 때 : 실근 없을 때,
	if (discriminant < 0)
		return (-1.0);
	// 두 근 중 작은 근 리턴
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}
