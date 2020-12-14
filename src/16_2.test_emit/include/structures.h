#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;
typedef struct s_hit_record t_hit_record;
typedef struct s_objects	t_objects;
typedef struct s_emit t_emit;
typedef struct s_plane t_plane;
typedef struct s_square t_square;

typedef int	t_bool;

# define FALSE 0
# define TRUE 1

typedef int	t_objects_type;

# define SP 0
# define LIGHT 1
# define PL	2
# define SQ 3

typedef int t_material_type;

# define PHONG 0

struct s_vec3
{
	double x;
	double y;
	double z;
};

struct	s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct	s_camera
{
	t_point3	orig;  // origin
	double		view_h; // viewport height;
	double		view_w; // viewport width;
	t_vec3		horizontal; // 수평방향 벡터
	t_vec3		vertical; // 수직방향 벡터
	double		focal_len; // focal length;
	t_point3	left_bottom; // lower left corner;
};

struct	s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio;
};

struct	s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
	t_color3	color;
};

struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_color3	color;
	t_bool		front_face;
};

struct s_objects
{
	t_objects_type	type;
	void			*element;
	void			*next;
	t_emit			*emit;
};

struct s_emit
{
	t_point3	center;
	t_color3	light_color;
	t_color3	light; // light_color * brightness;
	double		brightness;
	double		ka;
	double		ks;
	double		ksn;
	double		attenuationradius;
};

struct s_plane
{
	t_point3	p;
	t_vec3		normal;
	t_color3	color;
};

struct s_square
{
	t_point3	center;
	t_vec3		normal;
	double		side_len;
	t_color3	color;
	t_point3	min;
	t_point3	max;
};

#endif

