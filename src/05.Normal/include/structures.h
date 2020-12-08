#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;

typedef int	t_bool;

# define FALSE 0
# define TRUE 1

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
};

#endif
