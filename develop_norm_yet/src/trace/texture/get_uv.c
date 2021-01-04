#include "trace.h"

void	get_sphere_uv(t_hit_record *rec)
{
	double	theta;
	double	phi;

	theta = acos(-(rec->normal.y));
	phi = atan2(-(rec->normal.z), rec->normal.x) + M_PI;
	rec->u = phi / (2 * M_PI);
	rec->v = theta / M_PI;
}

void		get_disk_uv(t_hit_record *rec, t_cylinder *cy)
{
	if (cy->axis.x == 1)
	{
		rec->u = rec->p.z;
		rec->v = rec->p.y;
	}
	else if (cy->axis.y == 1)
	{
		rec->u = rec->p.x;
		rec->v = rec->p.z;
	}
	else
	{
		rec->u = rec->p.x;
		rec->v = rec->p.y;
	}
}

void	get_cylinder_uv(t_hit_record *rec, t_cylinder *cy)
{
	double	phi;

	phi = atan2(-(rec->normal.z), rec->normal.x) + M_PI;
	rec->u = phi / (2 * M_PI);
	rec->v = cy->height / (rec->p.y - cy->center_bottom.y) / M_PI;
}

void	get_square_uv(t_hit_record *rec, t_square *sq)
{
	double	inv_len;

	inv_len = 1 / sq->side_len;
	if (sq->normal.x != 0)
	{
		rec->u = (rec->p.z - sq->min.z) * inv_len;
		rec->v = (rec->p.y - sq->min.y) * inv_len;
	}
	else if (sq->normal.y != 0)
	{
		rec->u = (rec->p.x - sq->min.x) * inv_len;
		rec->v = (rec->p.z - sq->min.z) * inv_len;
	}
	else if (sq->normal.z != 0)
	{
		rec->u = (rec->p.x - sq->min.x) * inv_len;
		rec->v = (rec->p.y - sq->min.y) * inv_len;
	}
}