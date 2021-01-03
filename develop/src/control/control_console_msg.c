/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_console_msg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:25:53 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 19:31:18 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		console_msg_welcome(void)
{
	system("clear");
	ft_printf("* = * = * = * = * = * = * = * = * = *\n");
	ft_printf("*                                   *\n");
	ft_printf("*            WELCOME TO             *\n");
	ft_printf("*             KILEE's               *\n");
	ft_printf("*            Raytracer              *\n");
	ft_printf("*                                   *\n");
	ft_printf("* = * = * LIGHT ON / OFF * = * = * =*\n");
	ft_printf("=          [ SPACE BAR ]            =\n");
	ft_printf("* = * = * FILTER CHANGE  * = * = * =*\n");
	ft_printf("=          [   F key   ]            =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = *\n");
	ft_printf("***   MODE SWITCH by key press    ***\n");
	ft_printf("* = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=     O key : object mode           =\n");
	ft_printf("*     L key : light mode            *\n");
	ft_printf("*     C key : camera mode           *\n");
	ft_printf("=     T key : trace(render) mode    =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = *\n");
}

void		console_msg_welcome_save(void)
{
	system("clear");
	ft_printf("* = * = * = * = * = * = * = * = * = *\n");
	ft_printf("*                                   *\n");
	ft_printf("*            WELCOME TO             *\n");
	ft_printf("*             KILEE's               *\n");
	ft_printf("*            Raytracer              *\n");
	ft_printf("*                                   *\n");
	ft_printf("* = * = * = * SAVE MODE = * = * = * =\n");
}

void		console_msg_render_mode(void)
{
	system("clear");
	ft_printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	ft_printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	ft_printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	ft_printf("=             [ SPACE BAR ]                 =\n");
	ft_printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	ft_printf("=             [   F key   ]                 =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=              RENDER MODE                  =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=     --- --- ---            [ RENDER MODE ]=\n");
	ft_printf("*    | 1 | 2 |   |    1 : Phong render      *\n");
	ft_printf("=     --- --- ---     2 : Path_trace render =\n");
	console_msg_render_mode2();
}

void		console_msg_render_mode2(void)
{
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("= 1 : PHONG render                          =\n");
	ft_printf("=                                           =\n");
	ft_printf("* - Treat all object as phong diffuse model *\n");
	ft_printf("= - Only primary ray and Shadow ray         =\n");
	ft_printf("= - Sample per pixel(Antialiasing)          =\n");
	ft_printf("*                                           *\n");
	ft_printf("= 2 : PATH_TRACE render                     =\n");
	ft_printf("=                                           =\n");
	ft_printf("= - Treat material                          =\n");
	ft_printf("=   (Lambertain, Metal, Dielectric)         =\n");
	ft_printf("= - Sample per pixel(Antialiasing)          =\n");
	ft_printf("= - Scatter Depth                           =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}

void		console_msg_object_mode(void)
{
	system("clear");
	ft_printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	ft_printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	ft_printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	ft_printf("=             [ SPACE BAR ]                 =\n");
	ft_printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	ft_printf("=             [   F key   ]                 =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=            OBJECT MODE                    =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=         mouse                   [ SELECT ]=\n");
	ft_printf("*        ___ ___                            *\n");
	ft_printf("=       //  |   \\    L : select object      =\n");
	ft_printf("*      ||   O    |                          *\n");
	ft_printf("=      ||   |    |                          =\n");
	console_msg_object_mode2();
}
