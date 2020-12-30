#include "utils.h"

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

t_vec3	mmult_v(t_vec3 vec, double h, t_matrix44 *mtx)
{
	t_vec3	new;

	if (mtx == NULL)
		return (vec);
	new.x = vec.x * mtx->x[0][0] + vec.y * mtx->x[1][0] + vec.z * mtx->x[2][0] + h * mtx->x[3][0];
	new.y = vec.x * mtx->x[0][1] + vec.y * mtx->x[1][1] + vec.z * mtx->x[2][1] + h * mtx->x[3][1];
	new.z = vec.x * mtx->x[0][2] + vec.y * mtx->x[1][2] + vec.z * mtx->x[2][2] + h * mtx->x[3][2];
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

// 이동 + 회전이 합해진 변형 매트릭스로 가자 스케일은 적합하지 않은듯.
// - 스케일은 각각의 단일 객체의 값자체를 수정하는 방법으로 가는게 더 좋을듯
t_matrix44 *rotate(t_vec3 rotate)
{
	t_matrix44 *m_rotate;
	t_matrix44 *m_rotate_y;
	t_matrix44 *m_rotate_z;

	m_rotate = mrotate_x(rotate.x);
	m_rotate_y = mrotate_y(rotate.y);
	m_rotate_z = mrotate_z(rotate.z);
	mmult_m(m_rotate, m_rotate_y);
	mmult_m(m_rotate, m_rotate_z);
	free(m_rotate_y);
	free(m_rotate_z);
	m_rotate->rotate_deg = rotate;
	return (m_rotate);
}

t_matrix44 *inverse(t_matrix44 a)
{
	t_matrix44 *inv;
	int	i;
	int	j;
	int	k;
	double ratio;

	inv = munit();

	// Applying Gauss Jordan Elimination
	i = -1;
	while (++i < 4)
	{
		if (a.x[i][i] == 0.0)
		{
			perror("Matrix Inverse error! transform matirx can't have inverse");
			exit (1);
		}
		j = -1;
		while (++j < 4)
		{
			if (i != j)
			{
				ratio = a.x[j][i] / a.x[i][i];
				k = -1;
				while (++k < 4)
				{
					a.x[j][k] = a.x[j][k] - ratio * a.x[i][k];
					inv->x[j][k] = inv->x[j][k] - ratio * inv->x[i][k];
				}
			}
		}
	}
	// Row Operation to Make Principal Diagonal to 1
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			inv->x[i][j] = inv->x[i][j] / a.x[i][i];
	}
	return (inv);
}

t_matrix44	transpose(t_matrix44 *orig)
{
	t_matrix44 new;
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			new.x[i][j] = orig->x[j][i];
		}
	}
	return (new);
}

t_matrix44 *rotate_normal(t_matrix44 *rotate)
{
	t_matrix44 *rotate_normal;

	if (rotate == NULL)
		return (NULL);
	rotate_normal = inverse(*rotate);
	// transpose(rotate_normal);
	return (rotate_normal);
}
