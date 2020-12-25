#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "structures.h"

// utils.c
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
t_vec3	vdivide(t_vec3 vec, double t);
double	vdot(t_vec3 vec, t_vec3 vec2);
t_vec3	vcross(t_vec3 vec, t_vec3 vec2);
t_vec3	vunit(t_vec3 vec);
t_vec3	vmin(t_vec3 vec1, t_vec3 vec2);

// matrix44_utils.c
t_matrix44	*munit(void);
t_matrix44 *mmove(t_point3 move);
t_matrix44 *mrotate_x(double degree);
t_matrix44 *mrotate_y(double degree);
t_matrix44 *mrotate_z(double degree);
t_matrix44 *mscale(t_point3 scale);
t_vec3	mmult_v(t_vec3 vec, double h, t_matrix44 *mtx);
void  mmult_m(t_matrix44 *dst, t_matrix44 *src);
t_matrix44 *rotate(t_vec3 rotate);
t_matrix44 *rotate_normal(t_matrix44 *rotate);
t_matrix44 *inverse(t_matrix44 a);
void	transpose(t_matrix44 *orig);

// common_utils.c
double	deg_to_rad(double degrees);
double	saturate(double value);
t_bool	near_zero(t_vec3 *v);
double	random_double(void);
double	random_double_(double min, double max);
double	random_jitter(int sample_per_pixel, int k);
t_vec3		random_vec(void);
t_vec3		random_vec_(double min, double max);
t_vec3		random_in_unit_sphere(void);
t_vec3		random_unit_vector(void);
t_vec3 		random_in_hemisphere(t_vec3 *normal);


#endif
