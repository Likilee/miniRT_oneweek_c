#include "trace.h"

t_vec3	refract(t_vec3 *uv, t_vec3 *n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	// r_out_perp = etai_over_etat * (uv + cos_theta*n);
	// r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	cos_theta = fmin(vdot(vmult(*uv, -1), *n), 1.0);
	r_out_perp = vmult(vplus(*uv, vmult(*n, cos_theta)), etai_over_etat); // 𝐑′⊥
	r_out_parallel = vmult(*n, -sqrt(fabs(1.0 - vlength2(r_out_perp)))); // 𝐑′∥
	return (vplus(r_out_perp, r_out_parallel));
}
