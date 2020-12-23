#ifndef PARSE_H
# define PARSE_H

# include "structures.h"
# include "utils.h"
# include "scene.h"

t_scene		*read_rt(char *filepath);
void		parse_rt(t_scene *scene, char *line);
void		get_resolution(t_scene *scene, char *line);
void		get_ambient(t_scene *scene, char *line);
void		get_camera(t_scene *scene, char *line);
void		get_point_light(t_scene *scene, char *line);
void		get_sphere(t_scene *scene, char *line);
void		get_plane(t_scene *scene, char *line);
void		get_square(t_scene *scene, char *line);
void		get_cylinder(t_scene *scene, char *line);
void		get_triangle(t_scene *scene, char *line);

#endif
