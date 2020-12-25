#include "trace.h"

t_bool			in_shadow(t_objects *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	light_ray.dir = vunit(light_ray.dir);
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}
