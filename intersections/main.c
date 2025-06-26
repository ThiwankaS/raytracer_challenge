#include "ray.h"

int main (void)
{
	t_object *s = object_init(1, 0, 0, 0, SPHERE);
	t_intersect *i1 = intersection(-1, s);
	t_intersect *i2 = intersection(1, s);
	t_intersect *i3 = intersection(-5, s);
	t_intersect *i4 = intersection(-2, s);
	t_intersections *xs = NULL;

	xs = intersections(xs, i1);
	xs = intersections(xs, i2);
	xs = intersections(xs, i3);
	xs = intersections(xs, i4);

	t_intersections *current = xs;
	while(current)
	{
		printf("xs.intersect.value : %.2f\n", current->intersect->value);
		printf("xs.object.id : %d\n", current->intersect->object->id);
		printf("xs.count : %d\n\n", current->count);
		current = current->next;
	}
	t_intersect *result = hit(xs);
	printf("result.value : %.2f\n", result->value);
	printf("result.object.id : %d\n", result->object->id);
	free(s);
	free(i1);
	free(i2);
	free(i3);
	free(i4);
	t_intersections *temp = xs;
	while(xs)
	{
		temp = xs;
		xs = xs->next;
		free(temp);
	}
	return (0);
}
