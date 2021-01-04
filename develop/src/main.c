/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:50:55 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 16:17:26 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "mlx.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"
#include "scene.h"
#include "print.h"
#include "parse.h"
#include "control.h"

int		main(int argc, char **argv)
{
	t_cntl		cntl;

	if (argc == 2)
	{
		cntl_init(&cntl, argv[1]);
		my_mlx_welcome(&cntl);
		my_mlx_control(&cntl);
		return (0);
	}
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 10) != 0)
		{
			ft_printf("Error\n:Second arg must be \"--save\"");
			exit(0);
		}
		cntl_init(&cntl, argv[1]);
		console_msg_welcome_save();
		bmp_save_direct(&cntl);
		ft_printf(">> Close Ray TRACER, Bye Bye~~\n\n");
	}
	else
		ft_printf("Error\n: wrong argc\n");
	return (0);
}
