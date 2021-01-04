/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:09:26 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 21:36:53 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** 항등행렬 생성
**	1 0 0 0
**  0 1 0 0
**  0 0 1 0
**  0 0 0 1
*/

t_matrix44		*munit(void)
{
	t_matrix44	*matrix;
	int			i;
	int			j;

	if (!(matrix = (t_matrix44 *)malloc(sizeof(t_matrix44))))
		error_malloc();
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			matrix->x[i][j] = (i == j) ? 1 : 0;
	}
	return (matrix);
}

/*
** t_matrix44 *mmove(t_point3 move)
** {
** 	t_matrix44 *mtx;
**
** 	mtx = munit();
** 	mtx->x[3][0]  = move.x;
** 	mtx->x[3][1]  = move.y;
** 	mtx->x[3][2]  = move.z;
** 	return (mtx);
** }
*/

t_matrix44		*mrotate_x(double degree)
{
	t_matrix44	*mtx;
	double		theta;

	theta = deg_to_rad(degree);
	mtx = munit();
	mtx->x[1][1] = cos(theta);
	mtx->x[1][2] = sin(theta);
	mtx->x[2][1] = -sin(theta);
	mtx->x[2][2] = cos(theta);
	return (mtx);
}

t_matrix44		*mrotate_y(double degree)
{
	t_matrix44	*mtx;
	double		theta;

	theta = deg_to_rad(degree);
	mtx = munit();
	mtx->x[0][0] = cos(theta);
	mtx->x[0][2] = -sin(theta);
	mtx->x[2][0] = sin(theta);
	mtx->x[2][2] = cos(theta);
	return (mtx);
}

t_matrix44		*mrotate_z(double degree)
{
	t_matrix44	*mtx;
	double		theta;

	theta = deg_to_rad(degree);
	mtx = munit();
	mtx->x[0][0] = cos(theta);
	mtx->x[0][1] = sin(theta);
	mtx->x[1][0] = -sin(theta);
	mtx->x[1][1] = cos(theta);
	return (mtx);
}

/*
** rotate matrix 생성
*/

t_matrix44		*rotate(t_vec3 rotate)
{
	t_matrix44 *m_rotate;
	t_matrix44 *m_rotate_y;
	t_matrix44 *m_rotate_z;

	m_rotate = mrotate_x(rotate.x);
	m_rotate_y = mrotate_y(rotate.y);
	m_rotate_z = mrotate_z(rotate.z);
	mmult_m(m_rotate, m_rotate_y);
	mmult_m(m_rotate, m_rotate_z);
	free(m_rotate_y);
	free(m_rotate_z);
	m_rotate->rotate_deg = rotate;
	return (m_rotate);
}
