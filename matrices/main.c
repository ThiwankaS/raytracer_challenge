# include "matrix.h"

int main(void)
{
	t_tuple *tuple = createTuple(1.0, 2.0, 3.0, 0.0);
	t_matrix *m2 = matrix_init(4, 4);

	m2->data[0][0] = 1;
	m2->data[0][1] = 0;
	m2->data[0][2] = 0;
	m2->data[0][3] = 0;
	m2->data[1][0] = 0;
	m2->data[1][1] = 1;
	m2->data[1][2] = 0;
	m2->data[1][3] = 0;
	m2->data[2][0] = 3;
	m2->data[2][1] = 0;
	m2->data[2][2] = 1;
	m2->data[2][3] = 0;
	m2->data[3][0] = 0;
	m2->data[3][1] = 0;
	m2->data[3][2] = 0;
	m2->data[3][3] = 1;
	printf("m2 : \n");
	matrix_print(m2);
	printTuple(tuple, "original");
	t_tuple *resut = matrix_multiply_by_tuple(m2, tuple);
	printTuple(resut, "result");
	matrix_free(m2);
	free(tuple);
	free(resut);
	return (0);
}

/*
m1->data[0][0] = 1;
m1->data[0][1] = 2;
m1->data[0][2] = 6;
m1->data[0][3] = 6;
m1->data[1][0] = 1;
m1->data[1][1] = 2;
m1->data[1][2] = 6;
m1->data[1][3] = 6;
m1->data[2][0] = 1;
m1->data[2][1] = 2;
m1->data[2][2] = 6;
m1->data[2][3] = 6;
m1->data[3][0] = 1;
m1->data[3][1] = 2;
m1->data[3][2] = 6;
m1->data[3][3] = 6;
*/

/*
m1->data[0][0] = 1;
m1->data[0][1] = 2;
m1->data[0][2] = 6;
m1->data[1][0] = -5;
m1->data[1][1] = 8;
m1->data[1][2] = -4;
m1->data[2][0] = 2;
m1->data[2][1] = 6;
m1->data[2][2] = 4;
 */
