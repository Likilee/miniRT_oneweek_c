/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:25:54 by kihoonlee         #+#    #+#             */
/*   Updated: 2020/12/25 09:32:00 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
** 0. Mlx structures
*/
typedef struct s_data		t_data;
typedef struct s_scene		t_scene;

/*
** 1. common structures
*/
typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_hit_record	t_hit_record;
typedef struct s_matrix44	t_matrix44;

/*
** 2. scene structures
*/
typedef struct s_global		t_global;
typedef struct s_camera		t_camera;
typedef struct s_canvas		t_canvas;
typedef struct s_material	t_material;
typedef struct s_texture	t_texture;

/*
** 3. object structures
*/
typedef struct s_objects	t_objects;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_square		t_square;
typedef struct s_cylinder	t_cylinder;
typedef struct s_triangle	t_triangle;
typedef struct s_cube		t_cube;
typedef struct s_pyramid	t_pyramid;

/*
** 4. Identifier Macro
*/
typedef int					t_bool;

# define FALSE 0
# define TRUE 1

typedef int					t_objects_type;

# define SP 0
# define LIGHT 1
# define PL	2
# define SQ 3
# define CY 4
# define TR 5
# define CB 6
# define PM 7
# define CAM 11

typedef int					t_material_type;

# define DIFFUSE 0
# define METAL 1
# define DIELECTRIC 2
# define LAMBERTIAN 3

typedef int					t_texture_type;

# define SOLID 0
# define CHECKER 1
# define CHECKER_UV 2
# define RAINBOW 3

typedef int					t_light_type;

# define POINT 0
# define PARALLEL 1

/*
** 1. Common  structures
*/
struct						s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct						s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct						s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	t_material	*material;
	t_texture	*texture;
	double		tmin;
	double		tmax;
	double		t;
	double		u;
	double		v;
	t_bool		front_face;
};

struct						s_matrix44
{
	double	x[4][4];
};

/*
** 2. Scene structures
*/
struct						s_global
{
	t_color3	ambient;
	int			sample_per_pixel;
	int			depth;
};

/*
** camera member
** - orig = origin
** - dir = dir
** - horizontal = 수평방향 벡터
** - vertical = 수직방향 벡터
** - left_bottom = lower left corner;
*/
struct						s_camera
{
	t_point3	orig;
	t_point3	dir;
	double		hfov;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_point3	left_bottom;
};

/*
** canvas member
** - width = canvas width;
** - hegiht = canvas height;
*/
struct						s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
};

struct						s_material
{
	t_material_type	type;
	double			option1;
};

struct						s_texture
{
	t_texture_type	type;
	t_color3		albedo1;
	t_color3		albedo2;
	double			option1;
};

/*
** 0. Mlx structures
*/
struct						s_scene
{
	t_global	global;
	t_canvas	canv;
	t_camera	*cam_onair;
	t_objects	*cam_list;
	t_objects	*world;
};

struct						s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};
/*
** 3. Object structures
*/
struct						s_objects
{
	void			*element;
	t_matrix44		*rotate;
	t_matrix44		*rotate_normal;
	void			*next;
	t_objects_type	type;
};

struct						s_light
{
	t_point3		p;
	t_vec3			dir;
	t_color3		light_color;
	double			ka;
	t_light_type	type;
};

struct						s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
	t_material	*material;
	t_texture	*texture;
};

struct						s_plane
{
	t_point3	p;
	t_vec3		normal;
	t_material	*material;
	t_texture	*texture;

};

struct						s_square
{
	t_point3	center;
	t_vec3		normal;
	double		side_len;
	t_point3	min;
	t_point3	max;
	t_material	*material;
	t_texture	*texture;

};

struct						s_cylinder
{
	t_point3	center_bottom;
	t_point3	center_top;
	t_vec3		axis;
	double		radius;
	double		radius2;
	double		height;
	t_material	*material;
	t_texture	*texture;

};

struct						s_triangle
{
	t_point3	p0;
	t_point3	p1;
	t_point3	p2;
	t_vec3		p0p1;
	t_vec3		p1p2;
	t_vec3		p2p0;
	t_vec3		normal;
	t_material	*material;
	t_texture	*texture;
};

/*
** square[i] ordered: up,down,left,right,front,back
*/
struct						s_cube
{
	t_point3	center;
	double		side_len;
	t_square	*square[6];
	t_material	*material;
	t_texture	*texture;
};

struct						s_pyramid
{
	t_point3	top;
	t_point3	center;
	double		side_len;
	t_square	*bottom;
	t_triangle	*side[4];
	t_material	*material;
	t_texture	*texture;
};

#endif
