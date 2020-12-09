#include "scene.h"

t_light		*light(t_point3 light_origin, t_color3 light_color)
{
	t_light	*light;

	if(!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->p = light_origin;
	light->light_color = light_color;
	return (light);
};
