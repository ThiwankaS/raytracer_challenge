#include "ray.h"

int main (void)
{
	int light_x = 0, light_y = 0, light_z = -5;
	//int wall_z = 10;
	//double wall_size = 7.0;
	int width = 100, height = 100;
	//double pixel_size = width/wall_size;

	t_ray r;
	r.origin = point(light_x,light_y,light_z);
	r.direction = vector(0,0,1);
	t_tuple *color = point(1, 0, 0);
	t_object *s = object_init(1,0,0,0,SPHERE);
	t_canvas *canvas = init_canvas(width, height);


	free(r.direction);
	free(r.origin);
	matrix_free(s->transform);
	free(s);
	free(color);
	canvas_free(canvas);
	return (0);
}
