# include "matrix.h"

int main(void)
{
	t_matrix *m1 = matrix_init(3, 3);

	m1->data[0][0] = 3;
	m1->data[0][1] = 5;
	m1->data[0][2] = 0;
	m1->data[1][0] = 2;
	m1->data[1][1] = -1;
	m1->data[1][2] = -7;
	m1->data[2][0] = 6;
	m1->data[2][1] = -1;
	m1->data[2][2] = 5;

	matrix_print(m1);
	printf("\n");

	double res = matrix_minor(m1, 1, 0);
	printf("res %.2f \n", res);
	matrix_free(m1);
	return (0);
}
