/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect_lighting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:49:12 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 13:49:34 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool			scatter(t_ray *r_in, t_hit_rec *rec,
						t_color3 *attenuation, t_ray *scattered)
{
	t_bool	result;

	result = FALSE;
	if (rec->material->type == LAMBERTIAN)
		result = scatter_lambertian(rec, attenuation, scattered);
	else if (rec->material->type == METAL)
		result = scatter_metal(r_in, rec, attenuation, scattered);
	else if (rec->material->type == DIELECTRIC)
		result = scatter_dielectric(r_in, rec, attenuation, scattered);
	return (result);
}

t_bool			scatter_lambertian(t_hit_rec *rec, t_color3 *attenuation,
									t_ray *scattered)
{
	t_vec3 scatter_dir;

	scatter_dir = vplus(rec->normal, random_unit_vector());
	if (near_zero(&scatter_dir))
		scatter_dir = rec->normal;
	*scattered = ray(rec->p, scatter_dir);
	*attenuation = albedo(rec);
	return (TRUE);
}

/*
** option1 == fuzz
*/

t_bool			scatter_metal(t_ray *r_in, t_hit_rec *rec,
							t_color3 *attenuation, t_ray *scattered)
{
	t_vec3	reflected;

	reflected = reflect(vunit(r_in->dir), rec->normal);
	*scattered = ray(rec->p, vplus(reflected, vmult(random_in_unit_sphere(),
													rec->material->option1)));
	*attenuation = albedo(rec);
	return (vdot(scattered->dir, rec->normal) > 0);
}

/*
** Use Schlick's approximation for reflectance.
*/

static double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

/*
** option1 == ir (Index of Refraction)
*/

t_bool			scatter_dielectric(t_ray *r_in, t_hit_rec *rec,
									t_color3 *attenuation, t_ray *scattered)
{
	double	refraction_ratio;
	t_vec3	unit_dir;
	double	cos_theta;
	double	sin_theta;
	t_vec3	direction;

	*attenuation = color3(1.0, 1.0, 1.0);
	refraction_ratio = (rec->front_face) ? (1.0 / rec->material->option1)
										: rec->material->option1;
	unit_dir = vunit(r_in->dir);
	cos_theta = fmin(vdot(vmult(unit_dir, -1), rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (refraction_ratio * sin_theta > 1.0
		|| reflectance(cos_theta, refraction_ratio) > random_double())
		direction = reflect(unit_dir, rec->normal);
	else
		direction = refract(&unit_dir, &rec->normal, refraction_ratio);
	*scattered = ray(rec->p, direction);
	return (TRUE);
}
