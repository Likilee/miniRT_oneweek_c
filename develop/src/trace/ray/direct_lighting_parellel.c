#include "trace.h"

t_color3		direct_lighting_parallel(t_objects *objs, t_light *light, t_ray *r, t_hit_record *rec)
{
	t_color3	ambient;
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	t_color3	lightintensity;
	t_ray		light_ray;

	double		kd;
	double		ks;
	double		ksn;
	double		spec;
	light_ray.orig = vplus(rec->p, vmult(rec->normal, 0.0001));
	light_ray.dir = light->dir;
	if (in_shadow(objs, light_ray, INFINITY))
		return (color3(0,0,0));
	view_dir = vunit(vmult(r->dir, -1));
	reflect_dir = reflect(vmult(light->dir, -1), rec->normal);
	kd = fmax(vdot(rec->normal, light->dir), 0.0);// diffuse strength;
	ks = 0.3; // specular strength;
	ksn = rec->material->option1;
	ambient = vmult(light->light_color, light->ka);
	diffuse = vmult(light->light_color, kd);
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, kd), spec);
	// dprintf(2, "light_col:%f, %f, %f\n", light->light_color.x, light->light_color.y, light->light_color.z);
	// dprintf(2,"r->dir:%f, %f, %f\n", r->dir.x, r->dir.y, r->dir.z);
	// dprintf(2,"view_dir:%f, %f, %f\n", view_dir.x, view_dir.y, view_dir.z);
	// dprintf(2,"light->dir:%f, %f, %f\n", light->dir.x, light->dir.y, light->dir.z);
	// dprintf(2,"reflect_dir:%f, %f, %f\n", reflect_dir.x, reflect_dir.y, reflect_dir.z);
	// dprintf(2,"ka,kd,ks:%f, %f, %f\n", ka,kd,ks);
	// dprintf(2,"ambient:%f, %f, %f\n",ambient.x, ambient.y, ambient.z);
	// dprintf(2,"diffuse:%f, %f, %f\n",diffuse.x, diffuse.y, diffuse.z);
	// dprintf(2,"specula:%f, %f, %f\n\n",specular.x, specular.y, specular.z);
	lightintensity = vplus(vplus(ambient, diffuse),specular);
	return (lightintensity);
}
