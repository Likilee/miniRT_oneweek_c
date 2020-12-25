#include <stdio.h>
#include "structures.h"
#include "utils.h"
#include "ray.h"
#include "scene.h"
#include "print.h"

int	main(void)
{
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
	canv = canvas(1920, 1080);
	cam = camera(&canv, point3(0, 0, 0), 2.0, 1.0);
	objects = object(SP, sphere(point3(0, 0, -2), 0.5, color3(0.5, 0.3, 0.3)));
	oadd(&objects, object(SP, sphere(point3(0, -100.5, -1), 100, color3(0.2, 0.2, 0.2))));
	oadd(&objects, object(LIGHT, light(point3(3, 3, 0), color3(1, 0, 0))));
	oadd(&objects, object(LIGHT, light(point3(0, 3, 0), color3(0, 0, 1.0))));

	// Render
	// P3 means colors are in ASCII, then columns(width) and rows(height)
	printf("P3\n%d %d\n255\n", canv.width, canv.height);
	j = canv.height - 1;
	while (j >= 0)
	{
		dprintf(2, "Printing image :Line remain > %d\n", j);
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			r.orig = cam.orig;
			// left_bottom + u * horizontal + v * vertical - origin
			r.dir = vminus(vplus(vplus(cam.left_bottom, vmult(cam.horizontal, u)), vmult(cam.vertical, v)), cam.orig);
			// if (i == 200 && j == 150)
				pixel_color = ray_color(&r, objects);
			write_color(pixel_color);
		++i;
		}
	--j;
	}
	return (0);
}
