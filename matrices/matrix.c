# include "matrix.h"

int matrix_compare(t_matrix *m1, t_matrix *m2)
{
	if(!m1 || !m2)
		return (0);
	if(m1->row != m2->row || m1->column != m2->column)
		return (0);
	for(int i = 0; i < m1->row; i++)
	{
		for(int j = 0; j < m1->column; j++)
		{
			if(m1->data[i][j] != m2->data[i][j])
				return (0);
		}
	}
	return (1);
}

void matrix_print(t_matrix *m)
{
	if(!m)
		return ;
	for(int i = 0; i < m->row; i++)
	{
		for(int j = 0; j < m->column; j++)
		{
			printf("| %10.5f|",m->data[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

void matrix_free(t_matrix *m)
{
	for(int i = 0; i < m->row; i++)
		free(m->data[i]);
	free(m->data);
	free(m);
}

t_matrix *matrix_init(int row, int columns)
{
	t_matrix *m = calloc(1, sizeof(t_matrix));
	if(!m)
		return NULL;
	if (row <= 0 || columns <= 0)
		return NULL;
	m->data = calloc( row, sizeof(double *));
	if(!m->data)
		return NULL;
	m->row = row;
	m->column = columns;
	for(int i = 0;i < row; i++)
	{
		m->data[i] = calloc( columns, sizeof(double));
		if(!m->data)
		{
			for(int j = 0; j < i; j++)
			{
				free(m->data[j]);
			}
			free(m->data);
			return NULL;
		}
	}
	return m;
}

t_matrix *matrix_multiply(t_matrix *m1, t_matrix *m2)
{
	if(m1->row != 4 || m1->column != 4 || m2->row != 4 || m2->column != 4)
		return NULL;
	t_matrix *m = matrix_init(4,4);
	if(!m)
		return NULL;
	for(int i = 0;i < m->row; i++)
	{
		for(int j = 0;j < m->row; j++)
		{
			for(int k = 0; k < m->row; k++)
				m->data[i][j] += m1->data[i][k] * m2->data[k][j];
		}
	}
	return m;
}

t_tuple *matrix_multiply_by_tuple(t_matrix *m, t_tuple *t)
{
	if(!m || !t)
		return NULL;
	t_tuple *new = createTuple(0.0, 0.0, 0.0, 0.0);
	if(!new)
		return NULL;
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
			new->components[i] += (m->data[i][j] * t->components[j]);
	}
	return new;
}

t_matrix *matrix_transpose(t_matrix *m)
{
	t_matrix *t = matrix_init(4,4);
	if(!m || !t)
		return  NULL;
	for(int i = 0; i < m->row; i++)
	{
		for(int j = 0; j < m->column; j++)
			t->data[i][j] = m->data[j][i];
	}
	return t;
}

t_matrix *matrix_submatrix(t_matrix *m, int row, int column)
{
	int x, y;
	if(!m || m->column - 1 <= 1 || m->row - 1 <= 1)
		return NULL;
	t_matrix *sub = matrix_init(m->row - 1, m->column - 1);
	x = 0;
	for(int i = 0; i < m->row; i++)
	{
		if (i == row)
			continue;
		y = 0;
		for(int j = 0; j < m->column; j++)
		{
			if (j == column)
				continue;
			sub->data[x][y] = m->data[i][j];
			y++;
		}
		x++;
	}
	return sub;
}

double matrix_minor(t_matrix *m, int row, int column)
{
	double det = 0.0;
	t_matrix *temp = matrix_submatrix(m, row, column);
	if(!temp)
		return det;
	det = matrix_determinent(temp);
	matrix_free(temp);
	return det;
}

double matrix_cofactor(t_matrix *m, int row, int column)
{
	double det = matrix_minor(m, row, column);
	if((row + column) % 2 != 0)
		det = det * -1;
	return det;
}

double matrix_determinent(t_matrix *m)
{
	double det = 0.0;
	if(!m)
		return det;
	if(m->column == 2)
		det = m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
	else
	{
		for(int i = 0; i < m->column; i++)
			det += m->data[0][i] * matrix_cofactor(m, 0, i);
	}
	return det;
}

t_matrix *matrix_inverse(t_matrix *m)
{
	double det = matrix_determinent(m);
	if (det == 0.0)
		return NULL;
	t_matrix *cofactors = matrix_init(m->row, m->column);
	if(!m)
		return NULL;
	for(int i = 0; i < m->row; i++)
	{
		for(int j = 0; j < m->row; j++)
		{
			cofactors->data[i][j] = matrix_cofactor(m, i, j);
		}
	}
	t_matrix *transpose = matrix_transpose(cofactors);
	t_matrix *inverse = matrix_init(cofactors->row, cofactors->column);
	for(int i = 0; i < m->row; i++)
	{
		for(int j = 0; j < m->row; j++)
		{
			inverse->data[i][j] = transpose->data[i][j] / det;
		}
	}
	matrix_free(cofactors);
	matrix_free(transpose);
	return inverse;
}
