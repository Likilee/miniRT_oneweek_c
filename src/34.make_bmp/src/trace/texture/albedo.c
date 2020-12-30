#include "trace.h"

t_color3	albedo(t_hit_record *rec)
{
	if (rec->texture->type == SOLID)
		return (rec->texture->albedo1);
	else if (rec->texture->type == CHECKER)
		return (albedo_checker(rec));
	else if (rec->texture->type == CHECKER_UV)
		return (albedo_checker_uv(rec));
	else if (rec->texture->type == RAINBOW)
		return (albedo_rainbow_normal(rec));
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

t_color3	albedo_rainbow_normal(t_hit_record *rec)
{
	t_color3 rainbow;

	rainbow = color3(rec->normal.x +1.0, rec->normal.y + 1.0, rec->normal.z + 1.0);
	return (vmult(rainbow, 0.5));
}
