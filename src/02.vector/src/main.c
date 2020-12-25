#include <stdio.h>
#include "structures.h"
#include "utils.h"
#include "color.h"

int	main(void)
{
	int			i;
	int			j;
	t_color3	pixel_color;

	//Canvas
	int canvas_width = 256;
	int canvas_height = 256;

	//Render
	// P3 means colors are in ASCII, then columns(width) and rows(height)
	printf("P3\n%d %d\n255\n", canvas_width, canvas_height);
	j = canvas_height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canvas_width)
		{
			pixel_color.x = (double)i / (canvas_width - 1);
			pixel_color.y = (double)j / (canvas_height - 1);
			pixel_color.z = 0.25;
			write_color(pixel_color);
		++i;
		}
	--j;
	}
	return (0);
}
