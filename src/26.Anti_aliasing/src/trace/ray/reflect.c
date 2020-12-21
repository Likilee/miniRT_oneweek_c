#include "trace.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	//v - 2 * dot(v, n) * n;
	return (vminus(v, vmult(n ,vdot(v, n) * 2)));
}
