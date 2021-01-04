/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_console_msg2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:25:53 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 19:31:11 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void		console_msg_object_mode2(void)
{
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=       ---                [ ROTATE TOGGLE ]=\n");
	ft_printf("*      | R |   R : move <-> rotate          *\n");
	ft_printf("=       ---      ( switch QWE/ASD key )     =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("*                          [ MOVE / ROTATE ]*\n");
	ft_printf("=    X   Y   Z    < Axis                    =\n");
	ft_printf("*   --- --- ---                             *\n");
	ft_printf("=  | Q | W | E |  < Plus(Clockwise)         =\n");
	ft_printf("*   --- --- ---                             *\n");
	ft_printf("=  | A | S | D |  < Minus                   =\n");
	ft_printf("*   --- --- ---                             *\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=         ---                      [ SCALE ]=\n");
	ft_printf("*        | ^ |                              *\n");
	ft_printf("=     --- --- ---   ARROW_UP   : increase   =\n");
	ft_printf("*    |   | v |   |  ARROW_DOWN : decrease   *\n");
	ft_printf("      --- --- ---                           =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}

void		console_msg_camera_mode(void)
{
	system("clear");
	ft_printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	ft_printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	ft_printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	ft_printf("=             [ SPACE BAR ]                 =\n");
	ft_printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	ft_printf("=             [   F key   ]                 =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=            CAMERA MODE                    =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=       ---------                 [ SWITCH ]=\n");
	ft_printf("*      |   TAB   |      TAB : next camera   *\n");
	ft_printf("=       ---------                           =\n");
	console_msg_camera_mode2();
}

void		console_msg_camera_mode2(void)
{
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=           ---                     [ MOVE ]=\n");
	ft_printf("*          | W |        W : front           *\n");
	ft_printf("=       --- --- ---     A : left            =\n");
	ft_printf("*      | A | S | D |    S : back            *\n");
	ft_printf("=       --- --- ---     D : right           =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=       --- --- ---        [ ANGLE OF VIEW ]=\n");
	ft_printf("*      | Q |   | E |    Q : increase        *\n");
	ft_printf("=       --- --- ---     E : decrease        =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=         mouse                   [ ROTATE ]=\n");
	ft_printf("*        ___ ___        L     : turn left   *\n");
	ft_printf("=       //  |   \\       R     : turn right  =\n");
	ft_printf("*      ||   O    |      Wheel : up / down   *\n");
	ft_printf("=      ||   |    |                          =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}

void		console_msg_light_mode(void)
{
	system("clear");
	ft_printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	ft_printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	ft_printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	ft_printf("=              [ SPACE BAR ]                =\n");
	ft_printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	ft_printf("=             [   F key   ]                 =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=               LIGHT MODE                  =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=       ---------                 [ SWITCH ]=\n");
	ft_printf("*      |   TAB   |    TAB : next light      *\n");
	ft_printf("=       ---------                           =\n");
	console_msg_light_mode2();
}

void		console_msg_light_mode2(void)
{
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=      X   Y   Z    < Axis          [ MOVE ]=\n");
	ft_printf("*     --- --- ---                           *\n");
	ft_printf("=    | Q | W | E |  < Plus                  =\n");
	ft_printf("*     --- --- ---                           *\n");
	ft_printf("=    | A | S | D |  < Minus                 =\n");
	ft_printf("*     --- --- ---                           *\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	ft_printf("=         ---                 [ BRIGHTNESS ]=\n");
	ft_printf("*        | ^ |                              *\n");
	ft_printf("=     --- --- ---   ARROW_UP   : increase   =\n");
	ft_printf("*    |   | v |   |  ARROW_DOWN : decrease   *\n");
	ft_printf("      --- --- ---                           =\n");
	ft_printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}
