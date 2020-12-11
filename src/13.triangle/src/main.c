#include <stdio.h>
#include <time.h>
#include "structures.h"
#include "vec3_utils.h"
#include "ray.h"
#include "scene.h"
#include "print.h"

int	main(void)
{
	clock_t		start, end;
	double		result;

	start = clock();// 시간 측정 시작
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		r;
	t_objects	*objects;
	t_light		spot_light;

	//Scene setting;
	canv = canvas(600, 480);
	cam = camera(&canv, point3(0, 0, 0), 2.0, 1);
	objects = NULL;
	// objects = object(CY, cylinder(point3(0, 0, -2.5), vec3(0, 0, 0.5), 1.0, 2, color3(0.5, 0.1, 0.1)));
	// oadd(&objects, object(SP, sphere(point3(0, -100.5, -1), 100, color3(0.2, 0.2, 0.2))));
	objects = object(LIGHT, light(point3(0, 1, -2.8), color3(0.6, 1, 1)));
	oadd(&objects, object(SP, sphere(point3(0, 0, -1), 0.2, color3(0.5, 0.3, 0.3))));
	oadd(&objects, object(LIGHT, light(point3(1, 1.5, 0), color3(1, 1, 0.6))));
	oadd(&objects, object(SQ, square(point3(0, 0, -5), vec3(0, 0, 1), 5, color3(0.5, 0.5, 0.8))));
	oadd(&objects, object(SQ, square(point3(2.5, 0, -2.5), vec3(1, 0, 0), 5, color3(0.5, 0.5, 0.8))));
	oadd(&objects, object(SQ, square(point3(-2.5, 0, -2.5), vec3(1, 0, 0), 5, color3(0.5, 0.5, 0.8))));
	// oadd(&objects, object(SQ, square(point3(-1, 0, -2.5), vec3(1, 0, 0), 2, color3(0.5, 0.3, 0.2))));
	oadd(&objects, object(PL, plane(point3(0, 2.5, 0), vec3(0, -1, 0), color3(0.5, 0.5, 0.8))));
	oadd(&objects, object(PL, plane(point3(0, -2, 0), vec3(0, 1, 0), color3(0.5, 0.5, 0.8))));
	oadd(&objects, object(TR, triangle(point3(-2, 0.5, -3), point3(-2, -0.5, -3.5), point3(-2, -0.5,-2.5),color3(0.3, 0.5, 0.7))));
	oadd(&objects, object(TR, triangle(point3(0, 2.5, -3), point3(-2, -1, -3), point3(2, -1, -3),color3(0.3, 0.5, 0.7))));
	// oadd(&objects, object(PL, plane(point3(0, -0.5, 0), vec3(0, -1, 0), color3(0.3, 0.3, 0.3))));

	// Render
	// P3 means colors are in ASCII, then columns(width) and rows(height)
	printf("P3\n%d %d\n255\n", canv.width, canv.height);
	j = canv.height - 1;
	while (j >= 0)
	{
		// dprintf(2, "Printing image :Line remain > %d\n", j);
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			r.orig = cam.orig;
			// left_bottom + u * horizontal + v * vertical - origin
			r.dir = vunit(vminus(vplus(vplus(cam.left_bottom, vmult(cam.horizontal, u)), vmult(cam.vertical, v)), cam.orig));
			// if (i == 513 && j == 263)
			pixel_color = ray_color(&r, objects);
			write_color(pixel_color);
		++i;
		}
	--j;
	}
	end = clock(); // 시간 측정  끝!;
	//시간 측정 결과 출력
	result = (double)(end - start);
	dprintf(2, "프로그램 동작 시간:%f\n", result / CLOCKS_PER_SEC);
	return (0);
}
