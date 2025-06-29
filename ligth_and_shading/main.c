#include "3Dgraphic.h"

int main (void)
{
	t_material *m = material_init();
	t_tuple *position = point(0,0,0);

	t_tuple *eye = vector(0,0,-1);
	t_tuple *normal = vector(0,0,-1);
	t_tuple *p1 = point(0,0,10);
	t_tuple *color = point(1,1,1);
	t_light *light = point_light(p1, color);

	t_tuple *result = lighting(m, light, position, eye, normal);

	printTuple(result, "result");

	free(m->color);
	free(m);
	free(position);
	free(eye);
	free(normal);
	free(p1);
	free(color);
	free(light);
	free(result);
	return (0);
}
