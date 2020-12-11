#include "ray.h"

//ray 생성자
t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray new;

	new.orig = orig;
	new.dir = dir;
	return (new);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진점.
t_point3 ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_color3	ray_color(t_ray *r, t_objects *objs)
{
	t_vec3		unit_dir;
	t_vec3		n;
	double		t;
	t_hit_record rec;

	rec.tmin = 0.0001;
	rec.tmax = INFINITY;
	//광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면!)
	if (hit(objs, r, &rec))
	{
		// 빛을 찾아서어어~!
		
		return (phong_color(objs, r, &rec));
	}
	else
	{
		//구와 교점이 없으면 하늘로
		unit_dir = vunit(r->dir);
		t = 0.5 * (unit_dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
	}
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	//v - 2 * dot(v, n) * n;
	return (vminus(v, vmult(n ,vdot(v, n) * 2)));
}


t_color3		phong_color(t_objects *objs, t_ray *r, t_hit_record *rec)
{
	t_color3	light_color;
	t_objects	*objs_first;

	light_color = color3(0, 0, 0);
	objs_first = objs;
	while(objs)
	{
		if(objs->type == LIGHT)
			light_color = vplus(light_color, phong_color_get(objs_first, objs->element, r, rec));
		objs = objs->next;
	}
	// dprintf(2,"light_color:%f, %f, %f\n", light_color.x, light_color.y, light_color.z);
	return (vmin(vmult_(light_color, rec->color), color3(1, 1, 1)));
}

// (ambient + diffuse + specular) * objectColor * 감쇠율;

	// vec3 lightDir = normalize(lightPos - FragPos);

	// ambient
	//	float ambientStrength = 0.1;
    // vec3 ambient = ambientStrength * lightColor;

    // vec3 result = ambient * objectColor;

	// diffuse
	// float diff = max(dot(norm, lightDir), 0.0);
	// vec3 diffuse = diff * lightColor;

	// Specular
	// vec3 viewDir = normalize(viewPos - FragPos);
	// vec3 reflectDir = reflect(-lightDir, norm);
	// float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	// vec3 specular = specularStrength * spec * lightColor;
	// vec3 result = (ambient + diffuse + specular) * objectColor;

t_bool			in_shadow(t_objects *objs, t_ray light_ray, t_hit_record rec)
{
	double	light_len;
	light_len = vlength(light_ray.dir);
	rec.tmin = 0.0001;
	rec.tmax = light_len;
	light_ray.dir = vunit(light_ray.dir);
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

double			saturate(double value)
{
	if (value < 0)
		return (0);
	if (value > 1)
		return (1);
	return (value);
}


////https://lifeisforu.tistory.com/373?category=567143 여기 공식 참고
t_color3		phong_color_get(t_objects *objs, t_light *light, t_ray *r, t_hit_record *rec)
{
	t_color3	ambient;
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	t_color3	lightintensity;
	double		lightattenuation;
	double		distanceattenuation;
	double		lightradiusmask;
	double		AttenuationRadius;
	double		light_len;

	double		ka;
	double		kd;
	double		ks;
	double		ksn;
	double		spec;
	light_dir = vminus(light->p, rec->p);
	if (in_shadow(objs, ray(rec->p, light_dir), *rec))
		return (color3(0,0,0));
	light_len = vlength(light_dir);
	light_dir = vunit(light_dir);
	view_dir = vunit(vmult(r->dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), rec->normal);
	ka = 0.05; // ambient strength;
	kd = fmax(vdot(rec->normal, light_dir), 0.0);// diffuse strength;
	ks = 0.3; // specular strength;
	ksn = 256;
	ambient = vmult(light->light_color, ka);
	diffuse = vmult(light->light_color, kd);
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, kd), spec);
	// dprintf(2, "light_col:%f, %f, %f\n", light->light_color.x, light->light_color.y, light->light_color.z);
	// dprintf(2,"r->dir:%f, %f, %f\n", r->dir.x, r->dir.y, r->dir.z);
	// dprintf(2,"view_dir:%f, %f, %f\n", view_dir.x, view_dir.y, view_dir.z);
	// dprintf(2,"light_dir:%f, %f, %f\n", light_dir.x, light_dir.y, light_dir.z);
	// dprintf(2,"reflect_dir:%f, %f, %f\n", reflect_dir.x, reflect_dir.y, reflect_dir.z);
	// dprintf(2,"ka,kd,ks:%f, %f, %f\n", ka,kd,ks);
	// dprintf(2,"ambient:%f, %f, %f\n",ambient.x, ambient.y, ambient.z);
	// dprintf(2,"diffuse:%f, %f, %f\n",diffuse.x, diffuse.y, diffuse.z);
	// dprintf(2,"specula:%f, %f, %f\n\n",specular.x, specular.y, specular.z);
	lightintensity = vplus(vplus(ambient, diffuse),specular);
	AttenuationRadius = 8;
	lightradiusmask = pow(saturate(1 - pow((pow(light_len,2) / pow(AttenuationRadius,2)), 2)), 2);
	distanceattenuation = 1 / (pow((light_len),2) + 1);
	lightattenuation = distanceattenuation * lightradiusmask;
	return (vmult(lightintensity, lightattenuation));
}
