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

// 요기 포지셔닝 카메라파트 고대로! https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera
void	camera_set(t_canvas *canvas, t_camera *cam)
{
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

	lookat = vplus(cam->orig, cam->dir);
	vup = vec3(0,1,0); //up vector is y aixs unit vector
	theta = deg_to_rad(cam->hfov);
	half_width = tan(theta / 2);
	viewport_width = 2.0 * half_width;
	viewport_height = viewport_width / canvas->aspect_ratio;
	w = vunit(vmult(cam->dir, -1));
	// w = vunit(vminus(cam->orig, lookat));
	// if (w.x == 0 && w.z == 0)
	// 	w.x = 0.001;
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	cam->horizontal = vmult(u, viewport_width);
	cam->vertical = vmult(v, viewport_height);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam->left_bottom = vminus(vminus(vminus(cam->orig, vdivide(cam->horizontal, 2)),
								vdivide(cam->vertical, 2)), w);
}

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
	// if (w.x == 0 && w.z == 0)
	// 	w.x = 0.001;
	u = vunit(vcross(vup, w));
	v = vcross(w, u);

	cam.orig = lookfrom;
	cam.dir = lookat;
	cam.hfov = hfov;
	cam.horizontal = vmult(u, viewport_width);
	cam.vertical = vmult(v, viewport_height);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
								vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
	return (cam);
}
