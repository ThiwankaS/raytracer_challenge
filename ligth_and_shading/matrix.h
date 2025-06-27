# ifndef FT_MATRIX_H
# define FT_MATRIX_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include "tuple.h"

typedef struct s_matrix
{
	int row;
	int column;
	double **data;
} t_matrix;

void matrix_print(t_matrix *m);
void matrix_free(t_matrix *m);

int matrix_compare(t_matrix *m1, t_matrix *m2);

double matrix_determinent(t_matrix *m);
double matrix_minor(t_matrix *m, int row, int column);
double matrix_cofactor(t_matrix *m, int row, int column);

t_matrix *matrix_init(int row, int columns);
t_matrix *matrix_multiply(t_matrix *m1, t_matrix *m2);
t_matrix *matrix_transpose(t_matrix *m);
t_matrix *matrix_inverse(t_matrix *m);
t_matrix *matrix_submatrix(t_matrix *m, int row, int column);

t_tuple *matrix_multiply_by_tuple(t_matrix *m, t_tuple *t);

# endif
