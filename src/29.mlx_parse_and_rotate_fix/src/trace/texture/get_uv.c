#include "trace.h"

void	get_sphere_uv(t_hit_record *rec)
{
	double	theta;
	double	phi;

	theta = acos(-(rec->normal.y));
	phi = atan2(-(rec->normal.z), rec->normal.x) + M_PI;
	rec->u = phi / 2 * M_PI;
	rec->v = theta / 2 * M_PI;
}

void	get_cylinder_uv(t_hit_record *rec, t_cylinder *cy)
{
	double	phi;

	phi = atan2(-(rec->normal.z), rec->normal.x) + M_PI;
	rec->u = phi / 2 * M_PI;
	rec->v = cy->height / (rec->p.y - cy->center_bottom.y) / M_PI;
}
