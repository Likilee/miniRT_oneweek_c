/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:09:26 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 17:11:16 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** t_matrix44 *mscale(t_vec3 scale)
** {
** 	t_matrix44	*mtx;
**
** 	mtx = munit();
** 	mtx->x[0][0] = scale.x;
** 	mtx->x[1][1] = scale.y;
** 	mtx->x[2][2] = scale.z;
** 	return (mtx);
** }
*/

t_vec3			mmult_v(t_vec3 vec, double h, t_matrix44 *mtx)
{
	t_vec3	new;

	if (mtx == NULL)
		return (vec);
	new.x = vec.x * mtx->x[0][0]
			+ vec.y * mtx->x[1][0]
			+ vec.z * mtx->x[2][0]
			+ h * mtx->x[3][0];
	new.y = vec.x * mtx->x[0][1]
			+ vec.y * mtx->x[1][1]
			+ vec.z * mtx->x[2][1]
			+ h * mtx->x[3][1];
	new.z = vec.x * mtx->x[0][2]
			+ vec.y * mtx->x[1][2]
			+ vec.z * mtx->x[2][2]
			+ h * mtx->x[3][2];
	return (new);
}

/*
** matrix44 * matrix44
*/

void			mmult_m(t_matrix44 *dst, t_matrix44 *src)
{
	t_matrix44	new;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			new.x[i][j] = 0;
			while (++k < 4)
				new.x[i][j] += dst->x[i][k] * src->x[k][j];
		}
	}
	*dst = new;
}
