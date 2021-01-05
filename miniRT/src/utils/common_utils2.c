/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:43:57 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 15:47:51 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double		dmin3(double a, double b, double c)
{
	double min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

double		random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double		random_double_(double min, double max)
{
	return (min + (max - min) * random_double());
}

double		random_jitter(int spp, int k)
{
	if (spp == 1)
		return (0);
	else
		return (random_double() / (k % 4 + 1));
}

t_vec3		random_vec(void)
{
	return (vec3(random_double(), random_double(), random_double()));
}
