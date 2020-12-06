#include <stdio.h>

int	main(void)
{
	int		i;
	int		j;
	double	r;
	double	g;
	double	b;

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
			r = (double)i / (canvas_width - 1);
			g = (double)j / (canvas_height - 1);
			b = 0.25;
			printf("%d %d %d\n", (int)(255.999 * r), (int)(255.999 * g), (int)(255.999 * b));
		++i;
		}
	--j;
	}
	return (0);
}
