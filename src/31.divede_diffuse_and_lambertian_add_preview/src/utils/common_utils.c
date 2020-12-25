#include "utils.h"

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

t_bool	near_zero(t_vec3 *v)
{
	// 벡타가 모든 차원으로 0에 근접하면 트루 리턴
	double s = 1e-8;
	if ((v->x < s) && (v->y < s) && (v->z < s))
		return (TRUE);
	else
		return (FALSE);
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

t_vec3		random_vec(void)
{
	return (vec3(random_double(), random_double(), random_double()));
}

t_vec3		random_vec_(double min, double max)
{
	return (vec3(random_double_(min, max), random_double_(min, max), random_double_(min, max)));
}

t_vec3		random_in_unit_sphere(void)
{
	t_vec3	p;

	while(1)
	{
		p = random_vec_(-1, 1);
		if (vlength2(p) < 1)
			return (p);
	}
}

t_vec3		random_unit_vector(void)
{
	double	a;
	double	z;
	double	r;

	a = random_double_(0, 2 * M_PI);
	z = random_double_(-1, 1);
	r = sqrt(1 - z * z);
	return (vec3(r * cos(a), r * sin(a), z));
}

t_vec3 		random_in_hemisphere(t_vec3 *normal)
{
	t_vec3	in_unit_sphere;

	in_unit_sphere = random_in_unit_sphere();
	if (vdot(in_unit_sphere, *normal) > 0.0) // 법선과 같은 반구에 있으면
		return (in_unit_sphere);
	else
		return (vmult(in_unit_sphere, -1));
}

double		atod(char *str)
{
	char	**split;
	int		integer;
	double	point;
	int		n;
	double	num;

	split = ft_split(str, '.');
	integer = ft_atoi(split[0]);
	point = 0;
	if (split[1] != NULL)
	{
		point = ft_atoi(split[1]);
		n = ft_intlen(point);
		point /= pow(10, n);
		if (split[0][0] == '-')
			point *= -1;
	}
	num = integer + point;
	if (split[1] != NULL)
		ft_free_arr(split, 2);
	else
		ft_free_arr(split, 1);
	return (num);
}
