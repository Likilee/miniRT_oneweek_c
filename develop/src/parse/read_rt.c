/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:46:33 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 02:05:16 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_scene		*read_rt(char *filepath, void *mlx)
{
	t_scene *scene;
	int		fd;
	int		rd;
	char	*line;

	scene = scene_init();
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\n.rt file path wrong\n");
		exit(0);
	}
	rd = 1;
	while (rd)
	{
		rd = get_next_line(fd, &line);
		parse_rt(scene, line, mlx);
		free(line);
	}
	return (scene);
}

void		parse_rt(t_scene *scene, char *line, void *mlx)
{
	if (parse_rt_header(scene, line, mlx))
		return ;
	else if (parse_rt_bonus(scene, line, mlx))
		return ;
	else if (parse_rt_default(scene, line))
		return ;
	else
		parse_error_identifier(line);
}

t_bool		parse_rt_header(t_scene *scene, char *line, void *mlx)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, "R ", 2))
		get_resolution(scene, line);
	else if (ft_strnstr(line, "A ", 2))
		get_ambient(scene, line);
	else if (ft_strnstr(line, "L ", 2))
		get_lux(scene, line);
	else if (ft_strnstr(line, "BG ", 3))
		get_background(scene, line, mlx);
	else if (*line != '#' && *line != '\0')
		return (FALSE);
	return (TRUE);
}

t_bool		parse_rt_default(t_scene *scene, char *line)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, "sp ", 3))
		get_sphere(scene, line);
	else if (ft_strnstr(line, "pl ", 3))
		get_plane(scene, line);
	else if (ft_strnstr(line, "sq ", 3))
		get_square(scene, line);
	else if (ft_strnstr(line, "cy ", 3))
		get_cylinder(scene, line);
	else if (ft_strnstr(line, "tr ", 3))
		get_triangle(scene, line);
	else if (ft_strnstr(line, "c ", 2))
		get_camera(scene, line);
	else if (ft_strnstr(line, "l ", 2))
		get_point_light(scene, line);
	else
		return (FALSE);
	return (TRUE);
}

t_bool		parse_rt_bonus(t_scene *scene, char *line, void *mlx)
{
	while (*line == ' ')
		++line;
	if (ft_strnstr(line, "\tm ", 3))
		get_material(scene, line);
	else if (ft_strnstr(line, "\tt ", 3))
		get_texture(scene, line);
	else if (ft_strnstr(line, "\timg ", 5))
		get_texture_img(scene, line, mlx);
	else if (ft_strnstr(line, "cb ", 3))
		get_cube(scene, line);
	else if (ft_strnstr(line, "pm ", 3))
		get_pyramid(scene, line);
	else if (ft_strnstr(line, "dl ", 3))
		get_parallel_light(scene, line);
	else
		return (FALSE);
	return (TRUE);
}
