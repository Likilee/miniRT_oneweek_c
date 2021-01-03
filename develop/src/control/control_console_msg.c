#include "control.h"

void		console_msg_welcome(void)
{
	system("clear");
	printf("* = * = * = * = * = * = * = * = * = *\n");
	printf("*                                   *\n");
	printf("*            WELCOME TO             *\n");
	printf("*             KILEE's               *\n");
	printf("*            Raytracer              *\n");
	printf("*                                   *\n");
	printf("* = * = * LIGHT ON / OFF * = * = * =*\n");
	printf("=          [ SPACE BAR ]            =\n");
	printf("* = * = * FILTER CHANGE  * = * = * =*\n");
	printf("=          [   F key   ]            =\n");
	printf("* = * = * = * = * = * = * = * = * = *\n");
	printf("***   MODE SWITCH by key press    ***\n");
	printf("* = * = * = * = * = * = * = * = * = *\n");
	printf("=     O key : object mode           =\n");
	printf("*     L key : light mode            *\n");
	printf("*     C key : camera mode           *\n");
	printf("=     T key : trace(render) mode    =\n");
	printf("* = * = * = * = * = * = * = * = * = *\n");
}

void		console_msg_render_mode(void)
{
	system("clear");
	printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	printf("=             [ SPACE BAR ]                 =\n");
	printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	printf("=             [   F key   ]                 =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=              RENDER MODE                  =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=     --- --- ---            [ RENDER MODE ]=\n");
	printf("*    | 1 | 2 |   |    1 : Phong render      *\n");
	printf("=     --- --- ---     2 : Path_trace render =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("= 1 : PHONG render                          =\n");
	printf("=                                           =\n");
	printf("* - Treat all object as phong diffuse model *\n");
	printf("= - Only primary ray and Shadow ray         =\n");
	printf("= - Sample per pixel(Antialiasing)          =\n");
	printf("*                                           *\n");
	printf("= 2 : PATH_TRACE render                     =\n");
	printf("=                                           =\n");
	printf("* - Treat all object as phong diffuse model *\n");
	printf("= - Only primary ray and Shadow ray         =\n");
	printf("= - Sample per pixel(Antialiasing)          =\n");
	printf("= - Scatter Depth                           =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}

void		console_msg_object_mode(void)
{
	system("clear");
	printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	printf("=             [ SPACE BAR ]                 =\n");
	printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	printf("=             [   F key   ]                 =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=            OBJECT MODE                    =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=         mouse                   [ SELECT ]=\n");
	printf("*        ___ ___                            *\n");
	printf("=       //  |   \\    L : select object      =\n");
	printf("*      ||   O    |                          *\n");
	printf("=      ||   |    |                          =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=       ---                [ ROTATE TOGGLE ]=\n");
	printf("*      | R |   R : move <-> rotate          *\n");
	printf("=       ---      ( switch QWE/ASD key )     =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("*                          [ MOVE / ROTATE ]*\n");
	printf("=    X   Y   Z    < Axis                    =\n");
	printf("*   --- --- ---                             *\n");
	printf("=  | Q | W | E |  < Plus(Clockwise)         =\n");
	printf("*   --- --- ---                             *\n");
	printf("=  | A | S | D |  < Minus                   =\n");
	printf("*   --- --- ---                             *\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=         ---                      [ SCALE ]=\n");
	printf("*        | ^ |                              *\n");
	printf("=     --- --- ---   ARROW_UP   : increase   =\n");
	printf("*    |   | v |   |  ARROW_DOWN : decrease   *\n");
	printf("      --- --- ---                           =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}
void		console_msg_camera_mode(void)
{
	system("clear");
	printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	printf("=             [ SPACE BAR ]                 =\n");
	printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	printf("=             [   F key   ]                 =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=            CAMERA MODE                    =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=       ---------                 [ SWITCH ]=\n");
	printf("*      |   TAB   |      TAB : next camera   *\n");
	printf("=       ---------                           =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=           ---                     [ MOVE ]=\n");
	printf("*          | W |        W : front           *\n");
	printf("=       --- --- ---     A : left            =\n");
	printf("*      | A | S | D |    S : back            *\n");
	printf("=       --- --- ---     D : right           =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=       --- --- ---        [ ANGLE OF VIEW ]=\n");
	printf("*      | Q |   | E |    Q : increase        *\n");
	printf("=       --- --- ---     E : decrease        =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=         mouse                   [ ROTATE ]=\n");
	printf("*        ___ ___        L     : turn left   *\n");
	printf("=       //  |   \\       R     : turn right  =\n");
	printf("*      ||   O    |      Wheel : up / down   *\n");
	printf("=      ||   |    |                          =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}

void		console_msg_light_mode(void)
{
	system("clear");
	printf("* = * = * = * MODE SWITCH = * = * = * = * = *\n");
	printf("=  [ESC] [O]bject [L]ight [C]amera [T]race  =\n");
	printf("* = * = * =  LIGHT ON / OFF * = * = * = * = *\n");
	printf("=              [ SPACE BAR ]                =\n");
	printf("* = * = * = * FILTER CHANGE  * = * = * = * =*\n");
	printf("=             [   F key   ]                 =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=               LIGHT MODE                  =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=       ---------                 [ SWITCH ]=\n");
	printf("*      |   TAB   |    TAB : next light      *\n");
	printf("=       ---------                           =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=      X   Y   Z    < Axis          [ MOVE ]=\n");
	printf("*     --- --- ---                           *\n");
	printf("=    | Q | W | E |  < Plus                  =\n");
	printf("*     --- --- ---                           *\n");
	printf("=    | A | S | D |  < Minus                 =\n");
	printf("*     --- --- ---                           *\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
	printf("=         ---                 [ BRIGHTNESS ]=\n");
	printf("*        | ^ |                              *\n");
	printf("=     --- --- ---   ARROW_UP   : increase   =\n");
	printf("*    |   | v |   |  ARROW_DOWN : decrease   *\n");
	printf("      --- --- ---                           =\n");
	printf("* = * = * = * = * = * = * = * = * = * = * = *\n");
}
