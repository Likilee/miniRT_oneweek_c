#include "control.h"

void		cntl_object_translate_sp(t_cntl *cntl, t_vec3 *move)
{
	t_sphere *sp;

	sp = cntl->selected->element;
	sp->center = vplus(sp->center, *move);
}

void		cntl_object_translate_pl(t_cntl *cntl, t_vec3 *move)
{
	t_plane *pl;

	pl = cntl->selected->element;
	pl->p = vplus(pl->p, *move);
}

void		cntl_object_translate_sq(t_cntl *cntl, t_vec3 *move)
{
	t_square *sq;

	sq = cntl->selected->element;
	sq->center =  vplus(sq->center, *move);
	sq->min =  vplus(sq->min, *move);
	sq->max =  vplus(sq->max, *move);
}

void		cntl_object_translate_cy(t_cntl *cntl, t_vec3 *move)
{
	t_cylinder *cy;

	cy = cntl->selected->element;
	cy->center_bottom = vplus(cy->center_bottom, *move);
	cy->center_top = vplus(cy->center_top, *move);
}

void		cntl_object_translate_tr(t_cntl *cntl, t_vec3 *move)
{
	t_triangle *tr;

	tr = cntl->selected->element;
	tr->p0 = vplus(tr->p0, *move);
	tr->p1 = vplus(tr->p1, *move);
	tr->p2 = vplus(tr->p2, *move);
}
