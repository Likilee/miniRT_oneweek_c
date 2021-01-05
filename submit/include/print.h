/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:42:21 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 16:42:22 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "stdio.h"
# include "structures.h"
# include "mlx.h"
# include "utils.h"

/*
** src/print/color.c
*/
int		create_rgb(t_color3 *color);
int		get_r(int rgb);
int		get_g(int rgb);
int		get_b(int rgb);

/*
** src/print/filter.c
*/
void	filter(t_color3 *pixel_color, t_global *global);

/*
** src/print/image.c
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
