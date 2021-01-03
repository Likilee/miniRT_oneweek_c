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
