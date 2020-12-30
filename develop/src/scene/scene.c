#include "scene.h"

t_scene	*scene_init(void)
{
	t_scene *scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->world = NULL;
	scene->cam_list = NULL;
	scene->img = NULL;
	scene->global.ambient = color3(0.05, 0.05, 0.05);
	scene->global.spp = 1;
	scene->global.depth = 1;
	scene->global.lux = 300;
	return (scene);
}
