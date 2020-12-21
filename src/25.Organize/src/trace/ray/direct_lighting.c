#include "trace.h"

t_color3		direct_lighting(t_objects *objs, t_ray *r, t_hit_record *rec, t_global *global)
{
	t_color3	light_color;
	t_objects	*objs_first;

	light_color = color3(0, 0, 0);
	objs_first = objs;
	while(objs)
	{
		if(objs->type == LIGHT)
			light_color = vplus(light_color, direct_lighting_get(objs_first, objs->element, r, rec));
		objs = objs->next;
	}
	// dprintf(2,"light_color:%f, %f, %f\n", light_color.x, light_color.y, light_color.z);
	return (vmin(vmult_(light_color, albedo(rec)), color3(1, 1, 1)));
}

t_color3		direct_lighting_get(t_objects *objs, t_light *light, t_ray *r, t_hit_record *rec)
{
	if (light->type == POINT)
		return (direct_lighting_point(objs, light, r, rec));
	else if (light->type == PARALLEL)
		return (direct_lighting_parallel(objs, light, r, rec));
	return (color3(0,0,0));
}
