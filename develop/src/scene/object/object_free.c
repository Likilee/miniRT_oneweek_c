/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:24:09 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:24:10 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	free_cube(t_cube *cb)
{
	int		i;

	i = -1;
	while (++i < 6)
		free(cb->square[i]);
	free(cb);
}

void	free_pyramid(t_pyramid *pm)
{
	int		i;

	i = -1;
	while (++i < 4)
		free(pm->side[i]);
	free(pm->bottom);
	free(pm);
}
