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

// t_light		*light(t_point3 light_origin, t_color3 light_color)
// {
// 	t_light	*light;

// 	if(!(light = (t_light *)malloc(sizeof(t_light))))
// 		return (NULL);
// 	light->p = light_origin;
// 	light->light_color = light_color;
// 	return (light);
// };

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

t_square	*square(t_point3 p, t_vec3 normal, double side_len, t_color3 color)
{
	t_square	*sq;
	double		half_side;

	if(!(sq = (t_square *)malloc(sizeof(t_square))))
		return (NULL);
	half_side = side_len / 2;
	sq->center = p;
	sq->normal = normal;
	sq->color = color;
	sq->side_len = side_len;
	if (fabs(normal.x) == 1.0)
	{
		sq->min = vminus(p, vec3(0, half_side, half_side));
		sq->max = vplus(p, vec3(0, half_side, half_side));
	}
	else if (fabs(normal.y) == 1.0)
	{
		sq->min = vminus(p, vec3(half_side, 0, half_side));
		sq->max = vplus(p, vec3(half_side, 0, half_side));
	}
	else if (fabs(normal.z) == 1.0)
	{
		sq->min = vminus(p, vec3(half_side, half_side, 0));
		sq->max = vplus(p, vec3(half_side, half_side, 0));
	}
	else
	{
		perror("Wront normal intput to square!");
		exit(1);
	}
	return (sq);
}
