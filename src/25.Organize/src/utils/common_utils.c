#include "math_utils.h"

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double			saturate(double value)
{
	if (value < 0)
		return (0);
	if (value > 1)
		return (1);
	return (value);
}
