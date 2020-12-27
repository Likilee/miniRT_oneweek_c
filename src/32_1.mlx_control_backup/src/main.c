#include <stdio.h>
#include <time.h>
#include "mlx.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"
#include "scene.h"
#include "print.h"
#include "parse.h"
#include "control.h"

int	main(int argc, char **argv)
{
	t_scene		*scene;
	clock_t		start, end;
	double		result;

	if (argc == 2)
	{
		scene = read_rt(argv[1]);
		t_objects *temp;

		// temp = scene->world;
		// while (temp->type != CY)
		// {
		// 	temp = temp->next;
		// }
		// temp->rotate = rotate(vec3(0,0,45));
		// temp->rotate_normal = rotate_normal(temp->rotate);
		// oadd(&scene->world, object(CB, cube(point3(-1,1,-2), 2, material(DIELECTRIC, 1.5), texture(SOLID, color3(0.5,0.5,0), color3(0,0,0), 0))));
		// oadd(&scene->world, object(PM, pyramid(point3(2,2,-2), point3(2,3.5,-2), 2, material(METAL, 0), texture(SOLID, color3(0.1,0.5,0.3), color3(0,0,0), 0))));
		// temp = scene->world;
		// while (temp->type != PM)
		// {
		// 	temp = temp->next;
		// }
		// temp->rotate = rotate(vec3(-45,0,0));
		// temp->rotate_normal = rotate_normal(temp->rotate);
		// temp = scene->world;
		// while (temp->type != PL)
		// {
		// 	temp = temp->next;
		// }
		// temp->rotate = rotate(vec3(0,0,10));
		// temp->rotate_normal = rotate_normal(temp->rotate);
		// MLX setting;
		t_cntl	cntl;
		t_data  img;

		cntl.mlx = mlx_init();
		cntl.win = mlx_new_window(cntl.mlx, scene->canv.width, scene->canv.height, "Kilee's raytracer");
		img.img = mlx_new_image(cntl.mlx, scene->canv.width, scene->canv.width);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
		//global option
		scene->global.sample_per_pixel = 1;
		// Render
		scene->cam_onair = scene->cam_list->element;
		camera_set(&scene->canv, scene->cam_onair);
		// render(scene, &img);
		start = clock();// 시간 측정 시작
		render_preview(scene, &img);
		//시간 측정 결과 출력
		end = clock(); // 시간 측정  끝!;
		result = (double)(end - start);
		//랜더링된 이미지를 window로 띄웟!
		mlx_put_image_to_window(cntl.mlx, cntl.win, img.img, 0, 0);
		dprintf(2, "프로그램 동작 시간:%f\n", result / CLOCKS_PER_SEC);
		//mlx loop
		// mlx_loop(cntl.mlx);
		my_mlx_control(&cntl);
		return (0);
	}
	ft_printf("no argv\n");
	return (0);
}


// int	main(void)
// {
	// clock_t		start, end;
	// double		result;

	// start = clock();// 시간 측정 시작
// 	int			i;
// 	int			j;
// 	int			k;
// 	double		u;
// 	double		v;
// 	t_color3	pixel_color;
// 	t_canvas	canv;
// 	t_camera	cam;
// 	t_ray		r;
// 	t_objects	*objects;
// 	t_material	*diffuse;
// 	t_material	*metal;
// 	t_material	*glass;
// 	t_texture	*solid;
// 	t_texture	*checkered;
// 	t_texture	*checkered_uv;
// 	t_texture	*rainbow_normal;
// 	t_global	global;
// 	t_scene		scene;

// 	//Scene setting;

// 	global.ambient = color3(0.05, 0.05, 0.05);
// 	global.sample_per_pixel = 200;
// 	global.depth = 5;
// 	canv = canvas(1600, 900);
// 	cam = camera(&canv, point3(0,0,3.5),vec3(0,0,-1), 70);

	// t_matrix44 *rotate_pm;
	// t_matrix44 *rotate_sq;
	// t_matrix44 *rotate_cy;
	// rotate_pm = rotate(vec3(0,45,0));
	// rotate_sq = rotate(vec3(45,0,0));
	// rotate_cy = rotate(vec3(0,0,0));
	// objects = NULL;
	// diffuse = material(DIFFUSE, 32); // option1 is ksn;
	// metal = material(METAL, 0);
	// glass = material(DIELECTRIC, 1.5);
	// solid = texture(SOLID, color3(0.7,0.5,0.3), color3(0,0,0), 0);
	// checkered = texture(CHECKER, color3(0.5,0.1,0.1), color3(0.1,0.1,0.5), 5);
	// checkered_uv = texture(CHECKER_UV, color3(0.2, 0.5, 0.5), color3(0.8, 0.8, 0.8), 5);
	// rainbow_normal = texture(RAINBOW, color3(0,0,0), color3(0,0,0), 0);
	// // objects = object(CY, cylinder(point3(0, 0, -2.5), vec3(0, 0, 0.5), 1.0, 2, color3(0.5, 0.1, 0.1)));
	// // oadd(&objects, object(SP, sphere(point3(0, -100.5, -1), 100, diffuse, checkered), NULL));
	// oadd(&objects, object(SP, sphere(point3(-0.5, -1.5, -2), 0.5, glass, solid), NULL));
	// oadd(&objects, object(SP, sphere(point3(0.5, -1.5, -2), 0.5, metal, checkered_uv), NULL));
	// oadd(&objects, object(CB, cube(point3(-2, 1.5, -3), 1, metal, solid), rotate_sq));
	// // oadd(&objects, object(PM, pyramid(point3(1, 0.5, -2), point3(1, 2, -2), 2, diffuse, rainbow_normal), rotate_pm));
	// // oadd(&objects, object(SQ, square(point3(0, 0, -5), vec3(0, 0, 1), 5, diffuse), rotate_sq));
	// oadd(&objects, object(CY, cylinder(point3(0.6, 0, -3),vec3(0,0,1), 1, 2, diffuse, solid), rotate_cy));
	// oadd(&objects, object(LIGHT, light_point(point3(1.5, 3, -1.5), color3(6, 6, 6), 0.2), NULL));
	// oadd(&objects, object(LIGHT, light_point(point3(-3, 0, 0), color3(15, 15, 15), 0.1), NULL));
	// // oadd(&objects, object(LIGHT, light_parallel(vec3(1,-0.5,0), color3(2,2,2), 0.1), NULL));
	// // oadd(&objects, object(SQ, square(point3(2.5, 0, -2.5), vec3(1, 0, 0), 5, diffuse), NULL));
	// // oadd(&objects, object(SQ, square(point3(-2.5, 0, -2.5), vec3(1, 0, 0), 5, diffuse), NULL));
	// // oadd(&objects, object(SQ, square(point3(-1, 0, -2.5), vec3(1, 0, 0), 2, color3(0.5, 0.3, 0.2)), NULL));
	// // oadd(&objects, object(PL, plane(point3(0, 2.5, 0), vec3(0, -1, 0), diffuse, solid), NULL));
	// oadd(&objects, object(PL, plane(point3(0, -2.0, 0), vec3(0, 1, 0), diffuse, checkered), NULL));
	// oadd(&objects, object(TR, triangle(point3(-2, -0.5, -3.5), point3(-2, 0.5, -3),  point3(-2, -0.5,-2.5), diffuse, solid), NULL));
	// oadd(&objects, object(TR, triangle(point3(0, 2.5, -3), point3(-2, -1, -3), point3(2, -1, -3),color3(0.3, 0.5, 0.7))));

	// oadd(&objects, object(SP, sphere(point3(0, 0, 0), 0.5, color3(0.5, 0.3, 0.3)),  rotate_cy));

// 	// MLX setting;
// 	void    *mlx;
//     void    *mlx_win;
//     t_data  img;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, canv.width, canv.height, "Kilee's raytracer");
//     img.img = mlx_new_image(mlx, canv.width, canv.width);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//                                  &img.endian);

// 	// Render
// 	img = render(&scene);
// 	//시간 측정 결과 출력
// 	end = clock(); // 시간 측정  끝!;
// 	result = (double)(end - start);
// 	oclear(&objects);
// 	//랜더링된 이미지를 window로 띄웟!
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	dprintf(2, "프로그램 동작 시간:%f\n", result / CLOCKS_PER_SEC);
// 	//mlx loop
// 	mlx_loop(mlx);
// 	return (0);
// }
