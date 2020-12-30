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
	t_objects	*temp;
	t_cntl		cntl;
	t_data		img;

	if (argc == 2)
	{
		scene = read_rt(argv[1]);
		cntl.scene = scene;
		cntl.selected = NULL;
		cntl.mode = 0;
		cntl.light_on = 1;
		cntl_display_resolution(&cntl);
		cntl.mlx = mlx_init();
		cntl.win = mlx_new_window(cntl.mlx, scene->canv.width, scene->canv.height, "Kilee's raytracer");
		img.img = mlx_new_image(cntl.mlx, scene->canv.width, scene->canv.width);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
		cntl.img = &img;
		scene->img = &img;
		//global option
		scene->global.sample_per_pixel = 1;
		//first renderRender
		scene->cam_onair = scene->cam_list->element;
		camera_set(&scene->canv, scene->cam_onair);
		// render(scene, &img);
		// start = clock();// 시간 측정 시작
		// render_preview(cntl.scene, cntl.img);
		// //시간 측정 결과 출력
		render_preview(cntl.scene, cntl.img, cntl.light_on);
		mlx_put_image_to_window(cntl.mlx, cntl.win, cntl.img->img, 0, 0);
		//시간 측정 결과 출력
		my_mlx_control(&cntl); // while
		return (0);
	}
	ft_printf("no argv\n");
	return (0);
}
