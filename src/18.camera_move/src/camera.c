#include "scene.h"

// 요기 포지셔닝 카메라파트 고대로! https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera
t_camera	camera(t_canvas *canvas, t_point3 lookfrom, t_vec3 dir, double hfov)
{
	t_camera	cam;
	double 		theta;
	double 		half_width;
	double 		viewport_height;
	double 		viewport_width;
	double		focal_len = 1.0;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
	t_vec3		vup;
	t_vec3		lookat;

	lookat = vplus(lookfrom, dir);
	vup = vec3(0,1,0); //up vector is y aixs unit vector
	theta = deg_to_rad(hfov);
	half_width = tan(theta / 2);
	viewport_width = 2.0 * half_width;
	viewport_height = viewport_width / canvas->aspect_ratio;
	w = vunit(vminus(lookfrom, lookat));
	u = vunit(vcross(vup, w));
	v = vcross(w, u);

	cam.orig = lookfrom;
	cam.dir = lookat;
	cam.horizontal = vmult(u, viewport_width);
	cam.vertical = vmult(v, viewport_height);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
								vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
	return (cam);
}