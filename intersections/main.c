#include "ray.h"

int main (void)
{
	t_ray r;
	r.origin = point(1,2,3);
	r.direction = vector(0,1,0);

	t_matrix *m1 = translator(3,4,5);
	t_matrix *m2 = scalor(2,3,4);

	t_ray r1, r2;

	r1.origin = matrix_multiply_by_tuple(m1, r.origin);
	r1.direction = matrix_multiply_by_tuple(m1, r.direction);

	printTuple(r1.origin, "r1.origin");
	printTuple(r1.direction, "r1.dircetion");

	r2.origin = matrix_multiply_by_tuple(m2, r.origin);
	r2.direction = matrix_multiply_by_tuple(m2, r.direction);

	printTuple(r2.origin, "r2.origin");
	printTuple(r2.direction, "r2.dircetion");

	for(int i = 0; i < SIZE; i++)
		free(m1->data[i]);
	free(m1->data);
	free(m1);
	free(r.direction);
	free(r.origin);
	free(r1.direction);
	free(r1.origin);

	for(int i = 0; i < SIZE; i++)
		free(m2->data[i]);
	free(m2->data);
	free(m2);
	free(r2.direction);
	free(r2.origin);
	return (0);
}
