#include "ray.h"

int main (void)
{
	int light_x = 0, light_y = 0, light_z = -5;
	double wall_x, wall_y, wall_z = 10.0;
	double wall_size = 7.0;
	int width = 100, height = 100;
	double pixel_size = wall_size / width;

	t_ray r;
	r.origin = point(light_x,light_y,light_z);
	t_tuple *color = point(1, 0, 0);
	t_object *s = object_init(1,0,0,0,SPHERE);
	t_canvas *canvas = init_canvas(width, height);
	t_tuple *p, *temp;
	t_intersect *xs;

	for(int y = 0; y < (height -1); y++)
	{
		wall_y = (wall_size / 2) - (pixel_size * y);
		for(int x = 0; x <(width - 1); x++)
		{
			wall_x = (pixel_size * x) - (wall_size / 2);
			p = point(wall_x, wall_y, wall_z);
			temp = substrctTuples(p, r.origin);
			r.direction = normalize(temp);
			free(temp);
			xs = calculate_intersects(s, &r);
			if(xs && (xs[0].value >= 0 || xs[1].value >= 0))
				write_pixel(canvas, x, y, color);
			free(r.direction);
			free(p);
			free(xs);
		}
	}

	int fd = open("sphere.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	canvs_to_ppm(canvas, fd);
	close(fd);

	free(r.origin);
	matrix_free(s->transform);
	free(s);
	free(color);
	canvas_free(canvas);
	return (0);
}
