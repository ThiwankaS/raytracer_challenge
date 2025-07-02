# include "world.h"

int main(void)
{
	t_tuple *from = point(1,3,2);
	t_tuple *to = point(4,-2,8);
	t_tuple *up = vector(1,1,0);
	t_matrix *t1 = view_transformation(from, to, up);
	matrix_print(t1);
	matrix_free(t1);
	free(from);
	free(to);
	free(up);
	return (0);
}
