/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:15:54 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 16:18:43 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_camera	*camera_init(t_point3 lookfrom, t_vec3 look_dir, double hfov)
{
	t_camera *cam;

	if (!(cam = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	cam->orig = lookfrom;
	cam->dir = look_dir;
	cam->hfov = hfov;
	return (cam);
}

/*
** 기준 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,w)
** up vector is y aixs unit vector
*/

void		camera_set(t_canvas *canvas, t_camera *cam)
{
	t_cam_set	s;

	if (cam->dir.x == 0 && cam->dir.z == 0)
		cam->dir.z = 0.00001;
	s.lookat = vplus(cam->orig, cam->dir);
	s.vup = vec3(0.0, 1.0, 0.0);
	s.theta = deg_to_rad(cam->hfov);
	s.half_width = tan(s.theta / 2);
	s.viewport_width = 2.0 * s.half_width;
	s.viewport_height = s.viewport_width / canvas->aspect_ratio;
	s.w = vunit(vmult(cam->dir, -1));
	s.u = vunit(vcross(s.vup, s.w));
	s.v = vcross(s.w, s.u);
	cam->horizontal = vmult(s.u, s.viewport_width);
	cam->vertical = vmult(s.v, s.viewport_height);
	cam->left_bottom = vminus(vminus(vminus(cam->orig,
			vdivide(cam->horizontal, 2)), vdivide(cam->vertical, 2)), s.w);
}
