#include "scene.h"

t_scene	*scene_init(void)
{
	t_scene *scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->world = NULL;
	scene->cam_list = NULL;
	return (scene);
}
