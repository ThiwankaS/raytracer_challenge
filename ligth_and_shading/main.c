#include "3Dgraphic.h"

int main (void)
{
	t_object *s = object_init(1.0, 0.0, 0.0, 0.0, SPHERE);

	printf("default values : \n");
	printf("ambient   : %.2f\n", s->material->ambient);
	printf("diffiuse  : %.2f\n", s->material->diffiuse);
	printf("specular  : %.2f\n", s->material->specular);
	printf("shininess : %.2f\n", s->material->shininess);

	t_material *m = material_init();
	m->ambient = 1.0;
	free(s->material->color);
	free(s->material);
	s->material = m;

	printf("new values : \n");
	printf("ambient   : %.2f\n", s->material->ambient);
	printf("diffiuse  : %.2f\n", s->material->diffiuse);
	printf("specular  : %.2f\n", s->material->specular);
	printf("shininess : %.2f\n", s->material->shininess);

	free(s->material->color);
	matrix_free(s->transform);
	free(s);
	free(m);
	return (0);
}
