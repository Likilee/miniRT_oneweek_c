#include "scene.h"

t_sphere	*sphere(t_point3 center, double radius, t_color3 color)
{
	t_sphere *sp;

	if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	sp->color = color;
	return (sp);
}
