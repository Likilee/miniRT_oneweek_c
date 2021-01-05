/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:43:57 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 15:48:49 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int			saturate_min_max_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/*
** 벡터가 모든 차원으로 0에 근접하면 트루 리턴
*/

t_bool		near_zero(t_vec3 *v)
{
	double s;

	s = 1e-8;
	if ((v->x < s) && (v->y < s) && (v->z < s))
		return (TRUE);
	else
		return (FALSE);
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
		n = 0;
		while (split[1][n] == '0')
			++n;
		n += ft_intlen(point);
		point /= pow(10, n);
		if (split[0][0] == '-')
			point *= -1;
	}
	num = integer + point;
	ft_free_arr(split);
	return (num);
}
