/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:27:12 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:47:44 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	square_min_max_set(t_point3 *p, t_square *sq, double half_side)
{
	if (fabs(sq->normal.x) == 1.0)
	{
		sq->min = vminus(*p, vec3(0, half_side, half_side));
		sq->max = vplus(*p, vec3(0, half_side, half_side));
	}
	else if (fabs(sq->normal.y) == 1.0)
	{
		sq->min = vminus(*p, vec3(half_side, 0, half_side));
		sq->max = vplus(*p, vec3(half_side, 0, half_side));
	}
	else if (fabs(sq->normal.z) == 1.0)
	{
		sq->min = vminus(*p, vec3(half_side, half_side, 0));
		sq->max = vplus(*p, vec3(half_side, half_side, 0));
	}
	else
	{
		ft_printf("Error\n:** Wrong normal intput to square! **");
		exit(0);
	}
}

t_square	*square(t_point3 p, t_vec3 normal, double side_len)
{
	t_square	*sq;
	double		half_side;

	if (!(sq = (t_square *)malloc(sizeof(t_square))))
		error_malloc();
	half_side = side_len / 2;
	sq->center = p;
	sq->normal = normal;
	sq->side_len = side_len;
	square_min_max_set(&p, sq, half_side);
	return (sq);
}

t_cube		*cube(t_point3 center, double side)
{
	t_cube *cb;
	double h_side;

	if (!(cb = (t_cube *)malloc(sizeof(t_cube))))
		error_malloc();
	h_side = side / 2;
	cb->center = center;
	cb->side_len = side;
	cb->square[0] = square(vplus_(center, 0, h_side, 0), vec3(0, 1, 0), side);
	cb->square[1] = square(vplus_(center, 0, -h_side, 0), vec3(0, -1, 0), side);
	cb->square[2] = square(vplus_(center, -h_side, 0, 0), vec3(-1, 0, 0), side);
	cb->square[3] = square(vplus_(center, h_side, 0, 0), vec3(1, 0, 0), side);
	cb->square[4] = square(vplus_(center, 0, 0, h_side), vec3(0, 0, 1), side);
	cb->square[5] = square(vplus_(center, 0, 0, -h_side), vec3(0, 0, -1), side);
	return (cb);
}

t_pyramid	*pyramid(t_point3 center, t_point3 top, double side_len)
{
	t_pyramid	*pm;
	double		half_side;
	t_point3	p[4];

	if (!(pm = (t_pyramid *)malloc(sizeof(t_pyramid))))
		error_malloc();
	half_side = side_len / 2;
	pm->center = center;
	pm->top = top;
	pm->side_len = side_len;
	p[0] = vplus_(center, -half_side, 0, -half_side);
	p[1] = vplus_(center, -half_side, 0, half_side);
	p[2] = vplus_(center, half_side, 0, half_side);
	p[3] = vplus_(center, half_side, 0, -half_side);
	pm->bottom = square(center, vec3(0, 1, 0), side_len);
	pm->side[0] = triangle(top, p[0], p[1]);
	pm->side[1] = triangle(top, p[1], p[2]);
	pm->side[2] = triangle(top, p[2], p[3]);
	pm->side[3] = triangle(top, p[3], p[0]);
	return (pm);
}

t_triangle	*triangle(t_point3 p0, t_point3 p1, t_point3 p2)
{
	t_triangle	*tr;

	if (!(tr = (t_triangle *)malloc(sizeof(t_triangle))))
		error_malloc();
	tr->p0 = p0;
	tr->p1 = p1;
	tr->p2 = p2;
	tr->p0p1 = vminus(p1, p0);
	tr->p1p2 = vminus(p2, p1);
	tr->p2p0 = vminus(p0, p2);
	tr->normal = vunit(vcross(tr->p0p1, vminus(p2, p0)));
	return (tr);
}
