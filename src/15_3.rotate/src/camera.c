#include "scene.h"

t_camera	camera(t_canvas *canvas, t_point3 orig, double view_h, double focal_len)
{
	t_camera	cam;

	cam.orig = orig;
	cam.view_h = view_h;
	cam.view_w = view_h * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	cam.horizontal = vec3(cam.view_w, 0, 0);
	cam.vertical = vec3(0, cam.view_h, 0);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
								vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
	return (cam);
}
