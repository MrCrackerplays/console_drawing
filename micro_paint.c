#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	print_error(char *str)
{
	int	i;

	if (str == NULL)
		return (1);
	i = 0;
	while (str[i] != '\0')
		i++;
	write(2, "Error", 5);
	if (i > 0)
	{
		write(2, ": ", 2);
		write(2, str, i);
	}
	write(2, "\n", 1);
	return (1);
}

int	should_draw(char type, float x, float y, float rect_width, float rect_height, float i, float j)
{
	if ((x <= i && i <= x + rect_width) && (y <= j && j <= y + rect_height))
	{
		if (type == 'R')
			return (1);
		if ((x - (i - 1) < 1 && x - (i - 1) >= 0) || (x + rect_width - i < 1 && x + rect_width - i >= 0)
			|| (y - (j - 1) < 1 && y - (j - 1) >= 0) || (y + rect_height - j < 1 && y + rect_height - j >= 0))
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	int		canvas_width;
	int		canvas_height;
	char	background;

	if (argc != 2)
		return (print_error("argument"));
	file = fopen(argv[1], "r");
	if (file == NULL || fscanf(file, "%i %i %c\n", &canvas_width, &canvas_height, &background) != 3
		|| canvas_width < 1 || canvas_width > 300 || canvas_height < 1 || canvas_height > 300)
		return (print_error("Operation file corrupted"));

	char	*canvas;
	int		i;
	int		j;

	canvas = calloc((canvas_width + 1) * canvas_height, sizeof(char));
	if (canvas == NULL)
		return (1);
	i = 0;
	while (i < (canvas_width + 1) * canvas_height)
	{
		canvas[i] = background;
		i++;
	}
	j = 0;
	while (j < canvas_height)
	{
		canvas[(canvas_width + 1) * j + canvas_width] = '\n';
		j++;
	}

	int		value;
	char	type;
	float	x;
	float	y;
	float	rect_width;
	float	rect_height;
	char	character;

	value = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &rect_width, &rect_height, &character);
	while (value == 6)
	{
		if ((type != 'r' && type != 'R') || rect_width <= 0 || rect_height <= 0)
		{
			free(canvas);
			return (print_error("Operation file corrupted"));
		}

		j = 0;
		while (j < canvas_height)
		{
			i = 0;
			while (i < canvas_width)
			{
				if (should_draw(type, x, y, rect_width, rect_height, (float)i, (float)j))
					canvas[(canvas_width + 1) * j + i] = character;
				i++;
			}
			j++;
		}

		value = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &rect_width, &rect_height, &character);
	}
	if (value != EOF)
	{
		free(canvas);
		return (print_error("Operation file corrupted"));
	}


	write(1, canvas, (canvas_width + 1) * canvas_height);
	free(canvas);
	return (0);
}
