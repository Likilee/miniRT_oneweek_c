/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:15:59 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 21:36:41 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	*scene_init(void)
{
	t_scene *scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		error_malloc();
	scene->world = NULL;
	scene->cam_list = NULL;
	scene->img = NULL;
	scene->background = NULL;
	scene->global.ambient = color3(0.05, 0.05, 0.05);
	scene->global.spp = 1;
	scene->global.depth = 1;
	scene->global.lux = 300;
	scene->global.f_type = 0;
	return (scene);
}
