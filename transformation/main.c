#include "transform.h"

int main (void)
{
	t_canvas *canvas = init_canvas(900, 400);
	t_tuple *color = createTuple(1.0, 1.0, 1.0, 0.0);

	int radius = 100;
	int center_x = canvas->width / 2;
	int center_y = canvas->height / 2;

	t_tuple *center = createTuple(center_x, center_y, 0, 1);

	if(center_x >= 0 && center_x < canvas->width &&  center_y >= 0 && center_y < canvas->height)
			write_pixel(canvas, center->components[0], center->components[1], color);

	double angle = (2 * PI) / 12;
	for(int i = 0; i < 12; i++)
	{
		//drawing first point using a matrix
		t_tuple *point = createTuple(0,-radius,0,1);

		//rotate the point around z-axis step by step
		t_matrix *rotation = rotate_z_axis(i * angle);

		//calculate the rotaed point
		t_tuple *rotated = matrix_multiply_by_tuple(rotation, point);

		//calculate the distance from the center
		t_matrix *traslate = translator(center_x, center_y, 0);

		//final point need to plot on the canvas
		t_tuple *draw = matrix_multiply_by_tuple(traslate, rotated);

		//ploting the final point onm the canvas
		int x = draw->components[0];
		int y = draw->components[1];

		if(x >= 0 && x < canvas->width &&  y >= 0 && y < canvas->height)
			write_pixel(canvas, x, y, color);
		matrix_free(rotation);
		matrix_free(traslate);
		free(point);
		free(rotated);
		free(draw);
	}

	int fd = open("clock.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	canvs_to_ppm(canvas, fd);
	close(fd);

	for(int i = 0; i < canvas->height; i++)
		free(canvas->pixels[i]);
	free(canvas->pixels);
	free(canvas);
	free(color);
	free(center);
	return (0);
}
