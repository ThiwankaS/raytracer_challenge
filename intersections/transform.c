#include "transform.h"

t_matrix *translator(double x, double y, double z)
{
	t_matrix *m = matrix_init(4, 4);
	m->data[0][0] = 1;
	m->data[0][3] = x;
	m->data[1][1] = 1;
	m->data[1][3] = y;
	m->data[2][2] = 1;
	m->data[2][3] = z;
	m->data[3][3] = 1;
	return m;
}

t_matrix *scalor(double x, double y, double z)
{
	t_matrix *m = matrix_init(4, 4);
	m->data[0][0] = x;
	m->data[1][1] = y;
	m->data[2][2] = z;
	m->data[3][3] = 1;
	return m;
}

t_matrix *rotate_x_axis(double radian)
{
	t_matrix *m = matrix_init(4, 4);
	m->data[0][0] = 1;
	m->data[1][1] = cos(radian);
	m->data[1][2] = sin(radian) * (-1);
	m->data[2][1] = sin(radian);
	m->data[2][2] = cos(radian);
	m->data[3][3] = 1;
	return m;
}

t_matrix *rotate_y_axis(double radian)
{
	t_matrix *m = matrix_init(4, 4);
	m->data[0][0] = cos(radian);
	m->data[0][2] = sin(radian);
	m->data[1][1] = 1;
	m->data[2][0] = sin(radian) * (-1);
	m->data[2][2] = cos(radian);
	m->data[3][3] = 1;
	return m;
}

t_matrix *rotate_z_axis(double radian)
{
	t_matrix *m = matrix_init(4, 4);
	m->data[0][0] = cos(radian);
	m->data[0][1] = sin(radian) * (-1);
	m->data[1][0] = sin(radian);
	m->data[1][1] = cos(radian);
	m->data[2][2] = 1;
	m->data[3][3] = 1;
	return m;
}

t_matrix *shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
	t_matrix *m = matrix_init(4, 4);
	m->data[0][0] = 1;
	m->data[0][1] = xy;
	m->data[0][2] = xz;
	m->data[1][0] = yx;
	m->data[1][1] = 1;
	m->data[1][2] = yz;
	m->data[2][0] = zx;
	m->data[2][1] = zy;
	m->data[2][2] = 1;
	m->data[3][3] = 1;
	return m;
}
