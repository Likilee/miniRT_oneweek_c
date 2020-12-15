#include "ray.h"

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

t_color3	albedo(t_hit_record *rec)
{
	if (rec->texture->type == SOLID)
		return (rec->texture->albedo1);
	else if (rec->texture->type == CHECKER)
		return (albedo_checker(rec));
	else if (rec->texture->type == CHECKER_UV)
		return (albedo_checker_uv(rec));
	return (color3(0,0,0));
}

t_color3	albedo_checker(t_hit_record *rec)
{
	double sines;
	double density;

	density = rec->texture->option1;
	sines = sin(density * rec->p.x) * sin(density * rec->p.y) * sin(density * rec->p.z);
	if (sines < 0)
		return (rec->texture->albedo1);
	else
		return (rec->texture->albedo2);
}


t_color3	albedo_checker_uv(t_hit_record *rec)
{
	double sines;
	double density;

	density = rec->texture->option1;
	sines = sin(density * rec->u) * sin(density * rec->v);
	if (sines < 0)
		return (rec->texture->albedo1);
	else
		return (rec->texture->albedo2);
}
