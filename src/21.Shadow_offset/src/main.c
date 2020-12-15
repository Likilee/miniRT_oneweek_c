#include <stdio.h>
#include <time.h>
#include "structures.h"
#include "math_utils.h"
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
	t_material	*diffuse;
	t_texture	*solid;
	t_texture	*checkered;
	t_texture	*checkered_uv;
	t_texture	*rainbow_normal;
	t_global	global;

	global.ambient = color3(0.05, 0.05, 0.05);
	//Scene setting;

	canv = canvas(800, 600);
	cam = camera(&canv, point3(0,1,1),vec3(0,-0.1,-1), 90);

	t_matrix44 *rotate_cy;
	t_matrix44 *rotate_sq;
	rotate_cy = rotate(vec3(0,0,0));
	rotate_sq = rotate(vec3(0,-45,0));
	objects = NULL;
	diffuse = material(DIFFUSE, 32); // option1 is ksn;
	solid = texture(SOLID, color3(0.7,0.5,0.3), color3(0,0,0), 0);
	checkered = texture(CHECKER, color3(0.5,0.1,0.1), color3(0.1,0.1,0.5), 10);
	checkered_uv = texture(CHECKER_UV, color3(0.2, 0.5, 0.5), color3(0.8, 0.8, 0.8), 10);
	rainbow_normal = texture(RAINBOW, color3(0,0,0), color3(0,0,0), 0);
	// objects = object(CY, cylinder(point3(0, 0, -2.5), vec3(0, 0, 0.5), 1.0, 2, color3(0.5, 0.1, 0.1)));
	oadd(&objects, object(SP, sphere(point3(0, -100.5, -1), 100, diffuse, checkered), NULL));
	oadd(&objects, object(SP, sphere(point3(-0.5, 0, -2), 0.5, diffuse, rainbow_normal), NULL));
	// oadd(&objects, object(SQ, square(point3(0, 0, -5), vec3(0, 0, 1), 5, diffuse), rotate_sq));
	oadd(&objects, object(CY, cylinder(point3(0.6, -0.5, -3),vec3(0,1,0), 1, 1, diffuse, rainbow_normal), rotate_cy));
	// oadd(&objects, object(LIGHT, light(point3(0, 2.45, -3), color3(6, 6, 6), 0.2), NULL));
	oadd(&objects, object(LIGHT, light_point(point3(-1, 0, 0), color3(5, 5, 5), 0.1), NULL));
	oadd(&objects, object(LIGHT, light_parallel(vec3(1,-0.5,0), color3(2,2,2), 0.1), NULL));
	// oadd(&objects, object(LIGHT, light(point3(-1.5, 0, -1), color3(8, 8, 8), 0.1), NULL));
	// oadd(&objects, object(SQ, square(point3(2.5, 0, -2.5), vec3(1, 0, 0), 5, diffuse), NULL));
	// oadd(&objects, object(SQ, square(point3(-2.5, 0, -2.5), vec3(1, 0, 0), 5, diffuse), NULL));
	// oadd(&objects, object(SQ, square(point3(-1, 0, -2.5), vec3(1, 0, 0), 2, color3(0.5, 0.3, 0.2)), NULL));
	// oadd(&objects, object(PL, plane(point3(0, 2.5, 0), vec3(0, -1, 0), diffuse, solid), NULL));
	oadd(&objects, object(PL, plane(point3(0, -2.0, 0), vec3(0, 1, 0), diffuse, checkered), NULL));
	// oadd(&objects, object(TR, triangle(point3(-2, -0.5, -3.5), point3(-2, 0.5, -3),  point3(-2, -0.5,-2.5), diffuse, solid), NULL));
	// oadd(&objects, object(TR, triangle(point3(0, 2.5, -3), point3(-2, -1, -3), point3(2, -1, -3),color3(0.3, 0.5, 0.7))));

	// oadd(&objects, object(SP, sphere(point3(0, 0, 0), 0.5, color3(0.5, 0.3, 0.3)),  rotate_cy));


	// // matrix test;

	// for(int i = 0; i < 4; ++i)
	// 	dprintf(2, "%f %f %f %f\n", rotate_cy->x[i][0], rotate_cy->x[i][1], rotate_cy->x[i][2], rotate_cy->x[i][3]);
	// dprintf(2,"\n");
	// t_matrix44 *inv;
	// inv = inverse(*trans);
	// for(int i = 0; i < 4; ++i)
	// 	dprintf(2, "%f %f %f %f\n",inv->x[i][0],inv->x[i][1],inv->x[i][2],inv->x[i][3]);
	// dprintf(2,"\n");
	// transpose(inv);
	// for(int i = 0; i < 4; ++i)
	// 	dprintf(2, "%f %f %f %f\n",inv->x[i][0],inv->x[i][1],inv->x[i][2],inv->x[i][3]);
	// t_vec3 test = vec3(0, 0, 0);
	// test = mmult_v(test, 1, trans);
	// dprintf(2,"test:%f, %f, %f \n",test.x, test.y, test.z);

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
			// if (i == 720&& j == 445)
			pixel_color = ray_color(&r, objects, &global);
			pixel_color = vmin(vplus(pixel_color, global.ambient), color3(1,1,1)); // sum global_ambient + ray_color;
			write_color(pixel_color);
		++i;
		}
	--j;
	}
	//시간 측정 결과 출력
	end = clock(); // 시간 측정  끝!;
	result = (double)(end - start);
	oclear(&objects);
	dprintf(2, "프로그램 동작 시간:%f\n", result / CLOCKS_PER_SEC);
	return (0);
}
