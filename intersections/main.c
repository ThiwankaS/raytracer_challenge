#include "ray.h"

int main (void)
{
	t_ray r;
	r.origin = point(0,0,-5);
	r.direction = vector(0,0,1);

	t_object *s = object_init(1,0,0,0,SPHERE);
	t_matrix *m = translator(5,0,0);

	set_transform(s, m);

	t_intersect *xs = calculate_intersects(s, &r);

	printf("xs[0].t : %.2f\n", xs[0].value);
	printf("xs[1].t : %.2f\n", xs[1].value);

	free(r.direction);
	free(r.origin);
	matrix_free(s->transform);
	free(s);
	free(xs);
	return (0);
}
