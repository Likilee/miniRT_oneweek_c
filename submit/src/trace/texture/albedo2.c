/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albedo2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:17:31 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 15:25:05 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_color3	albedo(t_hit_rec *rec)
{
	if (rec->texture->type == SOLID)
		return (rec->texture->albedo1);
	else if (rec->texture->type == CHECKER)
		return (albedo_checker(rec));
	else if (rec->texture->type == CHECKER_UV)
		return (albedo_checker_uv(rec));
	else if (rec->texture->type == RAINBOW)
		return (albedo_rainbow_normal(rec));
	else if (rec->texture->type == IMAGE)
		return (albedo_image_uv(rec));
	else if (rec->texture->type == WAVE)
		return (albedo_wave(rec));
	return (color3(0, 0, 0));
}

t_color3	albedo_checker(t_hit_rec *rec)
{
	double sines;
	double density;

	density = rec->texture->option1;
	sines = sin(density * rec->p.x)
		* sin(density * rec->p.y)
		* sin(density * rec->p.z);
	if (sines < 0)
		return (rec->texture->albedo1);
	else
		return (rec->texture->albedo2);
}

t_color3	albedo_checker_uv(t_hit_rec *rec)
{
	double sines;
	double density;

	density = rec->texture->option1;
	sines = sin(density * rec->u) * sin(density * rec->v);
	if (sines < 0)
		return (rec->texture->albedo1);
	else
		return (rec->texture->albedo2);
}

t_color3	albedo_wave(t_hit_rec *rec)
{
	t_color3	wave;
	double		disrupt;
	double		interval;

	interval = rec->texture->option1;
	wave = rec->texture->albedo1;
	disrupt = (sin(rec->p.x * interval) + 1) * 0.5;
	wave.x = wave.x * disrupt;
	disrupt = (sin(rec->p.y * interval) + 1) * 0.5;
	wave.y = wave.y * disrupt;
	disrupt = (sin(rec->p.z * interval) + 1) * 0.5;
	wave.z = wave.z * disrupt;
	return (wave);
}
