#include "math_utils.h"

/* 항등행렬 생성
**	1 0 0 0
**  0 1 0 0
**  0 0 1 0
**  0 0 0 1
*/
t_matrix44	*munit(void)
{
	t_matrix44	*matrix;
	int			i;
	int			j;

	if(!(matrix = (t_matrix44 *)malloc(sizeof(t_matrix44))))
		return (NULL);
	i = -1;
	while(++i < 4)
	{
		j = -1;
		while (++j < 4)
			matrix->x[i][j] = (i == j) ? 1 : 0;
	}
	return (matrix);
}

t_matrix44 *mmove(t_point3 move)
{
	t_matrix44 *mtx;

	mtx = munit();
	mtx->x[3][0]  = move.x;
	mtx->x[3][1]  = move.y;
	mtx->x[3][2]  = move.z;
	return (mtx);
}

t_matrix44 *mrotate_x(double degree)
{
	t_matrix44	*mtx;
	double		theta;

	theta = deg_to_rad(degree);
	mtx = munit();
	mtx->x[1][1] = cos(theta);
	mtx->x[1][2] = sin(theta);
	mtx->x[2][1] = -sin(theta);
	mtx->x[2][2] = cos(theta);
	return (mtx);
}

t_matrix44 *mrotate_y(double degree)
{
	t_matrix44	*mtx;
	double		theta;

	theta = deg_to_rad(degree);
	mtx = munit();
	mtx->x[0][0] = cos(theta);
	mtx->x[0][2] = -sin(theta);
	mtx->x[2][0] = sin(theta);
	mtx->x[2][2] = cos(theta);
	return (mtx);
}

t_matrix44 *mrotate_z(double degree)
{
	t_matrix44	*mtx;
	double		theta;

	theta = deg_to_rad(degree);
	mtx = munit();
	mtx->x[0][0] = cos(theta);
	mtx->x[0][1] = sin(theta);
	mtx->x[1][0] = -sin(theta);
	mtx->x[1][1] = cos(theta);
	return (mtx);
}

t_matrix44 *mscale(t_vec3 scale)
{
	t_matrix44	*mtx;

	mtx = munit();
	mtx->x[0][0] = scale.x;
	mtx->x[1][1] = scale.y;
	mtx->x[2][2] = scale.z;
	return (mtx);
}

t_vec3	mmult_v(t_vec3 vec, t_matrix44 *mtx)
{
	t_vec3	new;

	new.x = vec.x * mtx->x[0][0] + vec.y * mtx->x[1][0] + vec.z * mtx->x[2][0] + mtx->x[3][0];
	new.y = vec.x * mtx->x[0][1] + vec.y * mtx->x[1][1] + vec.z * mtx->x[2][1] + mtx->x[3][1];
	new.z = vec.x * mtx->x[0][2] + vec.y * mtx->x[1][2] + vec.z * mtx->x[2][2] + mtx->x[3][2];
	return (new);
}

void  mmult_m(t_matrix44 *dst, t_matrix44 *src)
{
	t_matrix44 new;
	int i;
	int j;
	int k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			new.x[i][j]  = 0;
			while (++k < 4)
				new.x[i][j] += dst->x[i][k] * src->x[k][j];
		}
	}
	*dst = new;
}

t_matrix44 *transform(t_vec3 scale, t_vec3 rotate, t_vec3 move)
{
	t_matrix44 *m_trans;
	t_matrix44 *m_scale;
	t_matrix44 *m_rotate_x;
	t_matrix44 *m_rotate_y;
	t_matrix44 *m_rotate_z;
	t_matrix44 *m_move;

	m_trans = munit();
	m_scale = mscale(scale);
	m_rotate_x = mrotate_x(rotate.x);
	m_rotate_y = mrotate_y(rotate.y);
	m_rotate_z = mrotate_z(rotate.z);
	m_move = mmove(move);
	mmult_m(m_trans, m_scale);
	mmult_m(m_trans, m_rotate_x);
	mmult_m(m_trans, m_rotate_y);
	mmult_m(m_trans, m_rotate_z);
	mmult_m(m_trans, m_move);
	free(m_scale);
	free(m_rotate_x);
	free(m_rotate_y);
	free(m_rotate_z);
	free(m_move);
	return (m_trans);
}
