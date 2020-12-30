#include "scene.h"

void	free_cube(t_cube *cb)
{
	int		i;

	i = -1;
	while (++i < 6)
		free(cb->square[i]);
	free(cb);
}

void	free_pyramid(t_pyramid *pm)
{
	int		i;

	i = -1;
	while (++i < 4)
		free(pm->side[i]);
	free(pm->bottom);
	free(pm);
}
