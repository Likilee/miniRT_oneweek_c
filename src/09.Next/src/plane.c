#include "scene.h"

t_plane		*plane(t_point3 p, t_vec3 normal, t_color3 color)
{
	t_plane *pl;

	if(!(pl = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	pl->p = p;
	pl->normal = normal;
	pl->color = color;
	return (pl);
}
