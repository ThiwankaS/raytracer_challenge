# include "canvas.h"

t_tuple **init_pixels(int width, int height)
{
	t_tuple **pixels = calloc(height, sizeof(t_tuple *));
	if(!pixels)
		return (NULL);
	for(int i = 0; i < height; i++)
	{
		pixels[i] = calloc(width, sizeof(t_tuple));
		if(!pixels[i])
		{
			for(int j = 0; j < i; j++)
			{
				free(pixels[j]);
			}
			return NULL;
		}
	}
	return pixels;
}

t_canvas *init_canvas(int width, int height)
{
	t_canvas *canvas = calloc(1, sizeof(t_canvas));
	if (!canvas)
		return NULL;
	canvas->width = width;
	canvas->height = height;
	canvas->pixels = init_pixels(width, height);
	return canvas;
}

void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color)
{
	if(!canvas || !color)
		return;
	if(x < 0 && x >= canvas->width &&  y < 0 && y >= canvas->height)
		return;
	for(int i = 0; i < SIZE; i++)
		canvas->pixels[y][x].components[i] = color->components[i];
}

char *ft_strbuild(char *s1, char *s2)
{
	char *str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

int set_boundry(double value)
{
	int result = (int)value * 255;
	if (result > 255)
		result = 255;
	if (result < 0)
		result = 0;
	return result;
}

char *pixel_to_char(t_tuple *pixel)
{
	char *str = ft_itoa(set_boundry(pixel->components[0]));
	str = ft_strbuild(str, ft_strdup(" "));
	str = ft_strbuild(str, ft_itoa(set_boundry(pixel->components[1])));
	str = ft_strbuild(str, ft_strdup(" "));
	str = ft_strbuild(str, ft_itoa(set_boundry(pixel->components[2])));
	return str;
}

void canvs_to_ppm(t_canvas *canvas, int fd)
{
	char *str;

	write(fd,"P3", 2);

	write(fd, "\n", 1);

	str = ft_itoa(canvas->width);
	write(fd, str, strlen(str));
	free(str);

	write(fd," ", 1);

	str = ft_itoa(canvas->height);
	write(fd, str, strlen(str));
	free(str);

	write(fd, "\n", 1);

	str = ft_itoa(255);
	write(fd,str, strlen(str));
	free(str);

	write(fd, "\n", 1);

	for(int i = 0; i < canvas->height; i++)
	{
		for(int j = 0; j < canvas->width; j++)
		{
			str = pixel_to_char(&canvas->pixels[i][j]);
			write(fd,str, strlen(str));
			free(str);
			write(fd," ", 1);
		}
		write(fd, "\n", 1);
	}
}

void canvas_free(t_canvas *canvas)
{
	for(int i = 0; i < canvas->height; i++)
		free(canvas->pixels[i]);
	free(canvas->pixels);
	free(canvas);
}
