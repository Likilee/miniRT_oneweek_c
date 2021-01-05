/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:13:15 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:13:19 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

/*
** Sepia algorithm
** outputRed = (inputRed * .393) + (inputGreen *.769) + (inputBlue * .189)
** outputGreen = (inputRed * .349) + (inputGreen *.686) + (inputBlue * .168)
** outputBlue = (inputRed * .272) + (inputGreen *.534) + (inputBlue * .131)
*/

static void		filter_sepia(t_color3 *pixel_color)
{
	t_color3 temp;

	temp = *pixel_color;
	pixel_color->x = temp.x * 0.393 + temp.y * 0.769 + temp.z * 0.189;
	pixel_color->y = temp.x * 0.349 + temp.y * 0.686 + temp.z * 0.168;
	pixel_color->z = temp.x * 0.272 + temp.y * 0.534 + temp.z * 0.131;
}

static void		filter_red(t_color3 *pixel_color)
{
	pixel_color->y = 0.0;
	pixel_color->z = 0.0;
}

static void		filter_green(t_color3 *pixel_color)
{
	pixel_color->x = 0.0;
	pixel_color->z = 0.0;
}

static void		filter_blue(t_color3 *pixel_color)
{
	pixel_color->x = 0.0;
	pixel_color->y = 0.0;
}

void			filter(t_color3 *pixel_color, t_global *global)
{
	if (global->f_type == FILT_S)
		filter_sepia(pixel_color);
	else if (global->f_type == FILT_R)
		filter_red(pixel_color);
	else if (global->f_type == FILT_G)
		filter_green(pixel_color);
	else if (global->f_type == FILT_B)
		filter_blue(pixel_color);
	*pixel_color = vmin(*pixel_color, vec3(1.0, 1.0, 1.0));
}
