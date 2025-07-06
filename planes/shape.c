# include "shape.h"

t_object *sphere_init(void)
{
	t_object *sphere = object_init(1.0,0,0,0,SPHERE);
	return sphere;
}

t_object *plane_init(void)
{
	t_object *plane = object_init(0.0,0,0,0,PLANE);
	return plane;
}
