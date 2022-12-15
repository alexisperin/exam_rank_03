/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:03:25 by aperin            #+#    #+#             */
/*   Updated: 2022/12/15 13:58:08 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct s_draw
{
	int width;
	int height;
	char c;
	char **draw;
}t_draw;

typedef struct s_circle
{
	char type;
	float X;
	float Y;
	float radius;
	char c;
}t_circle;

int ft_write(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return (1);
}

int free_draw(t_draw *draw, int i)
{
	while (i >= 0)
	{
		free(draw->draw[i]);
		i--;
	}
	free(draw->draw);
	return (0);
}

void print_draw(t_draw *draw)
{
	int i = 0;
	while (i < draw->height)
	{
		ft_write(draw->draw[i]);
		write(1, "\n", 1);
		i++;
	}
}

int get_first_line(FILE *file, t_draw *draw)
{
	if (fscanf(file, "%d %d %c\n", &draw->width, &draw->height, &draw->c) != 3)
		return (0);
	if (draw->width <= 0 || draw->width > 300 || draw->height <= 0 || draw->height > 300)
		return (0);
	draw->draw = malloc(draw->height * sizeof(char *));
	if (!draw->draw)
		return (0);
	int i = 0;
	int j = 0;
	while (i < draw->height)
	{
		draw->draw[i] = malloc((draw->width + 1) * sizeof(char));
		if (!draw->draw[i])
			return (free_draw(draw, i - 1));
		j = 0;
		while (j < draw->width)
		{
			draw->draw[i][j] = draw->c;
			j++;
		}
		draw->draw[i][j] = 0;
		i++;	
	}
	return (1);
}

int in_circle(float i, float j, t_circle *c)
{
	float d = sqrtf(powf(c->X - j, 2) + powf(c->Y - i, 2));
	if (d <= c->radius)
		return (1);
	return (0);
}

int in_border(float i, float j, t_circle *c)
{
	float d = sqrtf(powf(c->X - j, 2) + powf(c->Y - i, 2));
	if (d > c->radius - 1)
		return (1);
	return (0);
}

void add_circle(t_draw *draw, t_circle *c)
{
	float i = 0;
	float j;

	while (i < draw->height)
	{
		j = 0;
		while (j < draw->width)
		{
			if (in_circle(i, j, c) && in_border(i, j, c))
				draw->draw[(int) i][(int) j] = c->c;
			if (c->type == 'C' && in_circle(i, j, c))
				draw->draw[(int) i][(int) j] = c->c;
			j++;
		}
		i++;
	}
}

int get_circles(FILE *file, t_draw *draw)
{
	t_circle c;
	int ret = fscanf(file, "%c %f %f %f %c\n", &c.type, &c.X, &c.Y, &c.radius, &c.c);
	while (ret == 5)
	{
		if ((c.type != 'c' && c.type != 'C') || c.radius <= 0)
			return (free_draw(draw, draw->height - 1));
		add_circle(draw, &c);
		ret = fscanf(file, "%c %f %f %f %c\n", &c.type, &c.X, &c.Y, &c.radius, &c.c);
	}
	if (ret == -1)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	FILE *file;
	t_draw	draw;

	if (ac != 2)
		return (ft_write("Error: argument\n"));
	file = fopen(av[1], "r");
	if (!file)
		return (ft_write("Error: Operation file corupted\n"));
	if (!get_first_line(file, &draw))
		return (ft_write("Error: Operation file corrupted\n"));
	if (!get_circles(file, &draw))
		return (ft_write("Error: Operation file corrupted\n"));
	fclose(file);
	print_draw(&draw);
	free_draw(&draw, draw.height - 1);
	return (0);
}
