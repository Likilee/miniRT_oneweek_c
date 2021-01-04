/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:43:57 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 15:50:56 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_vec3		random_vec_(double min, double max)
{
	return (vec3(random_double_(min, max),
				random_double_(min, max),
				random_double_(min, max)));
}

t_vec3		random_in_unit_sphere(void)
{
	t_vec3	p;

	while (1)
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

t_vec3		random_in_hemisphere(t_vec3 *normal)
{
	t_vec3	in_unit_sphere;

	in_unit_sphere = random_in_unit_sphere();
	if (vdot(in_unit_sphere, *normal) > 0.0)
		return (in_unit_sphere);
	else
		return (vmult(in_unit_sphere, -1));
}
