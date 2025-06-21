#include "canvas.h"

int main(void)
{
	t_canvas *canvas;

	canvas = init_canvas(5, 4);
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
	return (0);
}
