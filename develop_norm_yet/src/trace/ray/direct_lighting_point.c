#include "trace.h"

t_color3		direct_lighting_point(t_objects *objs, t_light *light, t_ray *r, t_hit_record *rec)
{
	t_color3	ambient;
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	t_color3	lightintensity;
	t_ray		light_ray;
	double		lightattenuation;
	double		distanceattenuation;
	double		lightradiusmask;
	double		AttenuationRadius;
	double		light_len;
	double		kd;
	double		ks;
	double		ksn;
	double		spec;

	light_dir = vminus(light->p, rec->p);
	light_len = vlength(light_dir);
	light_ray.orig = vplus(rec->p, vmult(rec->normal, 0.0001));
	light_ray.dir = light_dir;
	if (in_shadow(objs, light_ray, light_len))
		return (color3(0,0,0));
	light_len = vlength(light_dir);
	light_dir = vunit(light_dir);
	view_dir = vunit(vmult(r->dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), rec->normal);
	kd = fmax(vdot(rec->normal, light_dir), 0.0);// diffuse strength;
	ks = 0.3; // specular strength;
	ksn = rec->material->option1;
	ambient = vmult(light->light_color, light->ka);
	diffuse = vmult(light->light_color, kd);
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, kd), spec);
	// dft_printf(2, "light_col:%f, %f, %f\n", light->light_color.x, light->light_color.y, light->light_color.z);
	// dft_printf(2,"r->dir:%f, %f, %f\n", r->dir.x, r->dir.y, r->dir.z);
	// dft_printf(2,"view_dir:%f, %f, %f\n", view_dir.x, view_dir.y, view_dir.z);
	// dft_printf(2,"light_dir:%f, %f, %f\n", light_dir.x, light_dir.y, light_dir.z);
	// dft_printf(2,"reflect_dir:%f, %f, %f\n", reflect_dir.x, reflect_dir.y, reflect_dir.z);
	// dft_printf(2,"ka,kd,ks:%f, %f, %f\n", ka,kd,ks);
	// dft_printf(2,"ambient:%f, %f, %f\n",ambient.x, ambient.y, ambient.z);
	// dft_printf(2,"diffuse:%f, %f, %f\n",diffuse.x, diffuse.y, diffuse.z);
	// dft_printf(2,"specula:%f, %f, %f\n\n",specular.x, specular.y, specular.z);
	lightintensity = vplus(vplus(ambient, diffuse),specular);
	AttenuationRadius = 100;
	lightradiusmask = pow(saturate(1 - pow((pow(light_len,2) / pow(AttenuationRadius,2)), 2)), 2);
	distanceattenuation = 1 / (pow((light_len),2) + 1);
	lightattenuation = distanceattenuation * lightradiusmask;
	return (vmult(lightintensity, lightattenuation));
}
