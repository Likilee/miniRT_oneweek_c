#ifndef VEC3_UTILS_H
# define VEC3_UTILS_H

# include <math.h>
# include <stdlib.h>
# include "structures.h"
# include "stdio.h"

t_vec3	vec3(double x, double y, double z);
t_point3 point3(double x, double y, double z);
t_point3 color3(double r, double g, double b);
void	vset(t_vec3 *vec, double x, double y, double z);
double	vlength2(t_vec3 vec);
double	vlength(t_vec3 vec);
t_vec3	vplus(t_vec3 vec, t_vec3 vec2);
t_vec3	vplus_(t_vec3 vec, double x, double y, double z);
t_vec3	vminus(t_vec3 vec, t_vec3 vec2);
t_vec3	vminus_(t_vec3 vec, double x, double y, double z);
t_vec3	vmult(t_vec3 vec, double t);
t_vec3	vmult_(t_vec3 vec, t_vec3 vec2);
t_vec3	vdevide(t_vec3 vec, double t);
double	vdot(t_vec3 vec, t_vec3 vec2);
t_vec3	vcross(t_vec3 vec, t_vec3 vec2);
t_vec3	vunit(t_vec3 vec);


#endif
