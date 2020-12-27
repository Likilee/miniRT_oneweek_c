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
void		parse_error_identifier(char *line);
void		parse_error_data_count(char **data, int n, char *line);
void		parse_data_set_double(char **data, int n, char *line);
void		parse_data_set_zero_to_one(char **data, int n, char *line);
void		data_is_double(char *str, char *line);
void		data_is_zero_to_one(char *str, char *line);
void		data_is_in_degree_range(char *str, char *line);
void		parse_data_set_rgb(char **data, int n, char *line);


#endif
