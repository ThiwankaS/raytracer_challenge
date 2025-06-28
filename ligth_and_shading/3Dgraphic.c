#include "3Dgraphic.h"

t_tuple *normal_at(t_object *s, t_tuple *world_point)
{
	t_matrix *inverse = matrix_inverse(s->transform);
	t_tuple *abs_point = point(0,0,0);
	t_tuple *object_point = matrix_multiply_by_tuple(inverse, world_point);
	t_tuple *object_normal = substrctTuples(object_point, abs_point);
	t_matrix *trans = matrix_transpose(inverse);
	t_tuple *world_normal = matrix_multiply_by_tuple(trans, object_normal);
	free(abs_point);
	free(object_point);
	free(object_normal);
	matrix_free(inverse);
	matrix_free(trans);
	world_normal->components[3] = 0.0;
	t_tuple *normal = normalize(world_normal);
	free(world_normal);
	return normal;
}

t_tuple *reflect(t_tuple *in, t_tuple *normal)
{
	double product = dot(in, normal) * 2;
	t_tuple *t1 = scalerMultiplication(normal, product);
	t_tuple *t2 = substrctTuples(in, t1);
	free(t1);
	return t2;
}

t_light *point_light(t_tuple *position, t_tuple *intensity)
{
	t_light *light = calloc(1, sizeof(t_light));
	if(!light)
		return NULL;
	light->color = intensity;
	light->position = position;
	return light;
}
