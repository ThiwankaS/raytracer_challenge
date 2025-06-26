#include "ray.h"

int main (void)
{
	t_object *s = object_init(1, 0, 0, 0, SPHERE);
	t_intersect *i1 = intersection(5, s);
	t_intersect *i2 = intersection(7, s);
	t_intersect *i3 = intersection(-3, s);
	t_intersect *i4 = intersection(2, s);
	t_intersections *xs = intersections(4, i1, i2, i3, i4);

	for(int i = 0; i < xs->count; i++)
	{
		printf("xs.array[%d].t : %.2f\n", i, xs->array[i].value);
		printf("xs.array[%d].object.id : %d\n", i, xs->array[i].object->id);
	}
	
	free(s);
	free(i1);
	free(i2);
	free(i3);
	free(i4);
	free(xs->array);
	free(xs);
	return (0);
}
