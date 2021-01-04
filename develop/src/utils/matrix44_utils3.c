/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:09:26 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 17:11:28 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void		matrix_inverse_error(void)
{
	ft_printf("Error\n: ** Matrix Inverse error!can't have inverse");
	exit(0);
}

/*
** 4 * 4 matrix inverse by Gauss Jordan Eliminination
** 가우스 조던 소거법으로 4x4 역행렬 구하기
*/

static void		gauss_jordan(t_matrix44 *inv, t_matrix44 *a)
{
	int		i;
	int		j;
	int		k;
	double	ratio;

	i = -1;
	while (++i < 4)
	{
		if (a->x[i][i] == 0.0)
			matrix_inverse_error();
		j = -1;
		while (++j < 4)
		{
			if (i != j)
			{
				ratio = a->x[j][i] / a->x[i][i];
				k = -1;
				while (++k < 4)
				{
					a->x[j][k] = a->x[j][k] - ratio * a->x[i][k];
					inv->x[j][k] = inv->x[j][k] - ratio * inv->x[i][k];
				}
			}
		}
	}
}

/*
** Step1. gauss jordan
** Step2. Row operation to make Principal Diagonal to 1
*/

t_matrix44		*inverse(t_matrix44 a)
{
	t_matrix44	*inv;
	int			i;
	int			j;

	inv = munit();
	gauss_jordan(inv, &a);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			inv->x[i][j] = inv->x[i][j] / a.x[i][i];
	}
	return (inv);
}

t_matrix44		transpose(t_matrix44 *orig)
{
	t_matrix44	new;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			new.x[i][j] = orig->x[j][i];
		}
	}
	return (new);
}

t_matrix44		*rotate_normal(t_matrix44 *rotate)
{
	t_matrix44 *rotate_normal;

	if (rotate == NULL)
		return (NULL);
	rotate_normal = inverse(*rotate);
	return (rotate_normal);
}
