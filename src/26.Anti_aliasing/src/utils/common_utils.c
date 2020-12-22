#include "math_utils.h"

double		deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double		saturate(double value)
{
	if (value < 0)
		return (0);
	if (value > 1)
		return (1);
	return (value);
}

double		random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double		random_double_(double min, double max)
{
	return (min + (max - min) * random_double());
}

double		random_jitter(int sample_per_pixel, int k)
{
	if (sample_per_pixel == 1)
		return (0);
	else
		return (random_double() / (k % 4 + 1));
}
