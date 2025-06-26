# include "tuple.h"

/**
 * this funtion will chek for the last component of a given tuple and return
 * 1 is the component is 1.0 or 0 if te component is 0.0
*/
int isPoint(t_tuple *tuple)
{
	int index = SIZE - 1;
	double check = tuple->components[index];
	if (isEqual(check, 1.0))
		return (1);
	return (0);
}

/**
 * this function will print a given tuple in a much user freindly format
*/
void printTuple(t_tuple *tuple, char *str)
{
	printf(" %s : {{ ", str);
	for(int i = 0; i < SIZE;i++)
	{
		printf("%.2f", tuple->components[i]);
		if(i < (SIZE -1))
			printf(", ");
	}
	printf(" }}\n");
}

/**
 * by definition a tunple with last component as 0 is call a vector and if the
 * last xomponent is 1 it will call a point
*/
void whichTuple(t_tuple *tuple, char *str)
{
	if (isPoint(tuple))
		printf("%s is a point\n", str);
	else
		printf("%s is a vector\n", str);
}

/**
 * this function check wether two given tuple are eqaul or not, and print
 * the nature of thge two tuples
*/
void areEqual(t_tuple *t1, char *s1 , t_tuple *t2, char *s2)
{
	if(compareTuples(t1, t2))
		printf("%s and %s are equal\n", s1, s2);
	else
		printf("%s and %s are not equal\n", s1, s2);
}

/**
 * comparing two floating values
 * using eqaul sign is advisable hence need to cerate a custome function
 * EPSILON is the smallest error we tolerate when compare two double values
*/
bool isEqual(double a, double b)
{
	if(fabs(a - b) < EPSILON)
		return true;
	return false;
}

/**
 * this function will iterate though all the components of a tuple from first
 * element to the last and compare wether those are equal, if not immidiately
 * return false. If all the elements are eqaul then the two tuples said be
 * eqaul, then retrurn true
*/
bool compareTuples(t_tuple *t1, t_tuple *t2)
{
	for(int i = 0; i < SIZE;i++)
		if (!(isEqual(t1->components[i], t2->components[i])))
			return false;
	return true;
}

/**
 * this function will allocate and initialise a tupel on heap memory
*/
t_tuple *createTuple(double x, double y, double z, double w)
{
	t_tuple *tuple = malloc(sizeof(t_tuple));
	if(!tuple)
		return NULL;
	tuple->components[0] = x;
	tuple->components[1] = y;
	tuple->components[2] = z;
	tuple->components[3] = w;
	return tuple;
}

/**
 * adding two tuples
 */
t_tuple *addTuples(t_tuple *t1, t_tuple *t2)
{
	t_tuple *tuple = malloc(sizeof(t_tuple));
	if(!tuple)
		return NULL;
	for(int i = 0; i < SIZE;i++)
		tuple->components[i] = t1->components[i] + t2->components[i];
	return tuple;
}

/**
 * substrcating two tuples
*/
t_tuple *substrctTuples(t_tuple *t1, t_tuple *t2)
{
	t_tuple *tuple = malloc(sizeof(t_tuple));
	if(!tuple)
		return NULL;
	for(int i = 0; i < SIZE;i++)
		tuple->components[i] = t1->components[i] - t2->components[i];
	return tuple;
}
/**
 * this funtion will return the negative tuple
 */
t_tuple *negatingTuples(t_tuple *tuple)
{
	t_tuple *t = malloc(sizeof(t_tuple));
	if(!tuple)
		return NULL;
	for(int i = 0; i < SIZE;i++)
		t->components[i] = tuple->components[i] * (-1.0);
	return t;
}
/**
 * this function will return a poniter to a new tuple which is the same tuple
 * which all the elemnts has multiplied by the given scaler
 */
t_tuple *scalerMultiplication(t_tuple *tuple, double a)
{
	t_tuple *t = malloc(sizeof(t_tuple));
	if(!tuple)
		return NULL;
	for(int i = 0; i < SIZE;i++)
		t->components[i] = tuple->components[i] * a;
	return t;
}

/**
 * this function will return a poniter to a new tuple which is the same tuple
 * which all the elemnts has divide by the given divisor
 */
t_tuple *scalerDivision(t_tuple *tuple, double a)
{
	t_tuple *t = malloc(sizeof(t_tuple));
	if(!tuple)
		return NULL;
	for(int i = 0; i < SIZE;i++)
		t->components[i] = tuple->components[i] / a;
	return t;
}

/**
 * this function will return the normalizing vector for a given vector
 * if the magnitude is 0 then the null vector will return
 */
t_tuple *normalize(t_tuple *tuple)
{
	double length = magnitude(tuple);
	t_tuple *norm;
	if(isEqual(length, 0.00))
	{
		norm = createTuple(0.0, 0.0, 0.0, 0.0);
		return norm;
	}
	norm = malloc(sizeof(t_tuple));
	for(int i = 0; i < SIZE;i++)
		norm->components[i] = tuple->components[i] / length;
	return norm;
}

/**
 * this function is calculate and return cross prodcut of two
 * vectors
 */
t_tuple *cross(t_tuple *t1, t_tuple *t2)
{
	if(isPoint(t1) || isPoint(t2))
		return NULL;
	t_tuple *tuple = malloc(sizeof(t_tuple));
	if(!tuple)
		return NULL;
	double x1 = t1->components[0];
	double y1 = t1->components[1];
	double z1 = t1->components[2];
	double x2 = t2->components[0];
	double y2 = t2->components[1];
	double z2 = t2->components[2];
	tuple->components[0] = (y1 * z2 - z1 * y2);
	tuple->components[1] = (z1 * x2 - x1 * z2);
	tuple->components[2] = (x1 * y2 - y1 * x2);
	tuple->components[3] = 0.0;
	return tuple;
}

/**
 * this function will calculate and return the distance or the magnitute
 * of a vector, this magnitude will always be 0 for a point
 */
double magnitude(t_tuple *tuple)
{
	double total = 0.0, magnitude = 0.0;
	if(isPoint(tuple))
		return magnitude;
	for(int i = 0;i < SIZE;i++)
		total += pow(tuple->components[i], 2);
	magnitude = sqrt(total);
	return (magnitude);
}

/**
 * this function is calculate and return dot prodcut value of two
 * vectors
 */
double dot(t_tuple *t1, t_tuple *t2)
{
	double total = 0.0;
	if(isPoint(t1) || isPoint(t2))
		return total;
	for(int i = 0;i < SIZE; i++)
		total += t1->components[i] * t2->components[i];
	return total;
}
/**
 * creating a point base on the values passed
 */
t_tuple *point(double x, double y, double z)
{
	t_tuple *p = createTuple(x, y, z, 1.0);
	if(!p)
		return NULL;
	return p;
}
/**
 * creating a vector base on the values passed
 */
t_tuple *vector(double x, double y, double z)
{
	t_tuple *v = createTuple(x, y, z, 0.0);
	if(!v)
		return NULL;
	return v;
}
