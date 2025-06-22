#include "tuple.h"

int main(void)
{
	//creating tuples
	t_tuple *tuple1 = createTuple(3.0, -2.0, 5.0, 1.0);
	t_tuple *tuple2 = createTuple(-2.0, 3.0, 1.0, 0.0);
	t_tuple *tuple3 = createTuple(3.0, -2.0, 5.0, 1.0);
	t_tuple *tuple4 = createTuple(3.0, -2.0, 5.0, 0.0);

	//printing all the tuples
	printTuple(tuple1, "tuple1");
	printTuple(tuple2, "tuple2");
	printTuple(tuple3, "tuple3");
	printTuple(tuple4, "tuple4");

	//check  the type of the tuples
	whichTuple(tuple1, "tuple1");
	whichTuple(tuple2, "tuple2");

	//check the nature of tuples
	areEqual(tuple1, "tuple1", tuple3, "tuple3");
	areEqual(tuple1, "tuple1", tuple4, "tuple4");

	//adding two tuples
	t_tuple *tuple5 = addTuples(tuple1, tuple2);
	printTuple(tuple5, "tuple5");

	//substrcating two tuples
	t_tuple *tuple6 = createTuple(3.0, 2.0, 1.0, 1.0);
	t_tuple *tuple7 = createTuple(5.0, 6.0, 7.0, 1.0);
	printTuple(tuple6, "tuple6");
	printTuple(tuple7, "tuple7");
	t_tuple *tuple8 = substrctTuples(tuple6, tuple7);
	printTuple(tuple8, "tuple8");
	whichTuple(tuple8, "tuple8");

	//negating a tuple
	t_tuple *tuple9 = createTuple(1.0, -2.0, 3.0, 1.0);
	t_tuple *tuple10 = negatingTuples(tuple9);
	printTuple(tuple9, "tuple9");
	printTuple(tuple10, "tuple10");

	//scaler multiplication/division
	t_tuple *tuple11 = createTuple(1.0, -2.0, 3.0, 1.0);
	t_tuple *tuple12 = scalerMultiplication(tuple11, 2.0);
	printTuple(tuple11, "tuple11");
	printTuple(tuple12, "tuple12");

	//magnitute of a tuple
	t_tuple *tuple13 = createTuple(-1.0, -2.0, -3.0, 0.0);
	printTuple(tuple13, "tuple13");
	printf("magnitued of tuple13 is : %.5f \n", magnitude(tuple13));

	//normalizing a vector
	t_tuple *tuple14 = createTuple(1.0, 2.0, 3.0, 0.0);
	t_tuple *tuple15 = normalize(tuple14);
	printTuple(tuple14, "tuple14");
	printTuple(tuple15, "tuple15");
	printf("magnitued of tuple15 is : %.5f \n", magnitude(tuple15));

	//dot product of two vector
	t_tuple *tuple16 = createTuple(1.0, 2.0, 3.0, 0.0);
	t_tuple *tuple17 = createTuple(2.0, 3.0, 4.0, 0.0);
	printTuple(tuple16, "tuple16");
	printTuple(tuple17, "tuple17");
	printf("dot product : %.5f\n", dot(tuple16, tuple17));

	//cross product of two vectors
	t_tuple *tuple18 = createTuple(0.0, 1.0, 0.0, 0.0);
	t_tuple *tuple19 = createTuple(0.0, 0.0, 1.0, 0.0);
	printTuple(tuple18, "tuple18");
	printTuple(tuple19, "tuple19");
	t_tuple *tuple20 = cross(tuple18, tuple19);
	printTuple(tuple20, "tuple20");

	//releasing heap allocated memory
	free(tuple1);
	free(tuple2);
	free(tuple3);
	free(tuple4);
	free(tuple5);
	free(tuple6);
	free(tuple7);
	free(tuple8);
	free(tuple9);
	free(tuple10);
	free(tuple11);
	free(tuple12);
	free(tuple13);
	free(tuple14);
	free(tuple15);
	free(tuple16);
	free(tuple17);
	free(tuple18);
	free(tuple19);
	free(tuple20);
	return (0);
}
