# include "world.h"

int main(void)
{
	t_world *world = world_init();
	t_camera *camera = camera_init(11, 11, PI/2);
	t_tuple *from = point(0,0,-5);
	t_tuple *to   = point(0,0,1);
	t_tuple *up   = point(0,1,0);

	printTuple(from, "from");
	printTuple(to, "to");
	printTuple(up, "up");
	t_matrix *m = view_transformation(from, to, up);

	t_canvas *image = render(camera, world);
	t_tuple *pixel = image->pixels[5];
	printTuple(pixel, "pixel");
	matrix_print(m);
	matrix_free(camera->transform);
	free(camera);
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	list_clear(world->object_list);
	free(world);
	free(from);
	free(to);
	free(up);
	canvas_free(image);
	return (0);
}
