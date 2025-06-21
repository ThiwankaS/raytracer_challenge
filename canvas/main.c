#include "canvas.h"

int main(void)
{
	t_canvas *canvas;

	canvas = init_canvas(2, 3);
	for(int i = 0; i < canvas->height; i++)
	{
		for(int j = 0; j < canvas->width; j++)
		{
			printf("canvas.pixel[%d][%d] : ", i, j);
			printTuple(&canvas->pixels[i][j], "p");
		}
	}

	t_tuple *color = createTuple(1.0, 2.0, 3.0, 0.0);
	write_pixel(canvas, 1, 2, color);

	for(int i = 0; i < canvas->height; i++)
	{
		for(int j = 0; j < canvas->width; j++)
		{
			printf("canvas.pixel[%d][%d] : ", i, j);
			printTuple(&canvas->pixels[i][j], "p");
		}
	}

	for(int i = 0; i < canvas->height; i++)
		free(canvas->pixels[i]);
	free(canvas->pixels);
	free(canvas);
	free(color);
	return (0);
}
