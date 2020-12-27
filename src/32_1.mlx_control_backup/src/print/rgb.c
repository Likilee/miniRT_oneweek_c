#include "print.h"

int		create_rgb(t_color3 *color)
{
	int r;
	int g;
	int b;

	r = (int)(255.999 * color->x);
	g = (int)(255.999 * color->y);
	b = (int)(255.999 * color->z);
	return (0 << 24 | r << 16 | g << 8 | b);
}

int		get_r(int rgb)
{
	return (rgb & (0xff << 16));
}

int		get_g(int rgb)
{
	return (rgb & (0xff << 8));
}

int		get_b(int rgb)
{
	return (rgb & 0xff);
}

