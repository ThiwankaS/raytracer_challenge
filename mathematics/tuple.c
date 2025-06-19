#include <stdio.h>
#include <math.h>

#define SIZE 4
#define EPSILON 0.00001
typedef struct s_tuple
{
	double components[SIZE];
} t_tuple;

int isPoint(t_tuple *tuple)
{
	int index = SIZE - 1;
	double check = tuple->components[index];
	if (fabs(check - 1.0) < EPSILON)
		return (1);
	return (0);
}

void whichTuple(t_tuple *tuple, char *str)
{
	if (isPoint(tuple))
		printf("%s is a point\n", str);
	else
		printf("%s is a vector\n", str);
}

int main(void)
{
	t_tuple tuple1 = {{ 1.3, 2.7, -6.9 , 1.0}};
	t_tuple tuple2 = {{ 1.3, 2.7, -6.9 , 0.0}};
	whichTuple(&tuple1, "tuple1");
	whichTuple(&tuple2, "tuple2");
	return (0);
}
