# ifndef FT_TUPLE_H
# define FT_TUPLE_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# define SIZE 4
# define EPSILON 0.00001

typedef struct s_tuple
{
	double components[SIZE];
} t_tuple;

/**
 * funtion declaration
*/
int isPoint(t_tuple *tuple);

void printTuple(t_tuple *tuple, char *str);
void whichTuple(t_tuple *tuple, char *str);
void areEqual(t_tuple *t1, char *s1 , t_tuple *t2, char *s2);

bool isEqual(double a, double b);
bool compareTuples(t_tuple *t1, t_tuple *t2);

t_tuple *createTuple(double x, double y, double z, double w);
t_tuple *addTuples(t_tuple *t1, t_tuple *t2);
t_tuple *substrctTuples(t_tuple *t1, t_tuple *t2);
t_tuple *negatingTuples(t_tuple *tuple);
t_tuple *scalerMultiplication(t_tuple *tuple, double a);
t_tuple *scalerDivision(t_tuple *tuple, double a);
t_tuple *normalize(t_tuple *tuple);
t_tuple *cross(t_tuple *t1, t_tuple *t2);

double magnitude(t_tuple *tuple);
double dot(t_tuple *t1, t_tuple *t2);
# endif
