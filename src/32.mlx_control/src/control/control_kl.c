#include "control.h"

// int			cntl_object_select(int button, int x, int y, t_cntl *cntl)
// {
// 	double	u;
// 	double	v;
// 	t_ray	r;
// 	t_hit_record rec;

// 	printf("button: %d, x:%d, y:%d\n",button, x, y);
// 	u = (double)x / (cntl->scene->canv.width - 1);
// 	v = (double)y / (cntl->scene->canv.height - 1);
// 	r.orig = cntl->scene->cam_onair->orig;
// 	r.dir = vunit(vminus(vplus(vplus(cntl->scene->cam_onair->left_bottom, vmult(cntl->scene->cam_onair->horizontal, u)), vmult(cntl->scene->cam_onair->vertical, v)), cntl->scene->cam_onair->orig));
// 	hit(cntl->scene, &ray, &rec);
// 	return (0);
// }

/*
** u = (double)i / (scene->canv.width - 1);
	v = (double)j / (scene->canv.height - 1);
	r.orig = scene->cam_onair->orig;
	r.dir = vunit(vminus(vplus(vplus(scene->cam_onair->left_bottom, vmult(scene->cam_onair->horizontal, u)), vmult(scene->cam_onair->vertical, v)), scene->cam_onair->orig));
*/
