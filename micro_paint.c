/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:11:42 by aperin            #+#    #+#             */
/*   Updated: 2022/12/15 14:00:56 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_drawing
{
	int width;
	int height;
	char c;
	char **draw;
}t_drawing;

typedef struct s_rect
{
	char type;
	float X;
	float Y;
	float width;
	float height;
	char c;
}t_rect;

int ft_write(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return (1);
}

int get_first_line(FILE *file, t_drawing *drawing)
{
	if (fscanf(file, "%d %d %c\n", &drawing->width, &drawing->height, &drawing->c) != 3)
		return (0);
	if (drawing->width <= 0 || drawing->width > 300 || drawing->height <= 0 || drawing->height > 300)
		return (0);
	drawing->draw = malloc(drawing->height * sizeof(char *));
	if (!drawing->draw)
		return (0);
	int i = 0;
	while (i < drawing->height)
	{
		drawing->draw[i] = malloc((drawing->width + 1) * sizeof(char));
		if (!drawing->draw[i])
		{
			i--;
			while(i >= 0)
			{
				free(drawing->draw[i]);
				i--;
			}
			free(drawing->draw);
			return (0);
		}
		i++;
	}
	i = 0;
	int j;
	while (i < drawing->height)
	{
		j = 0;
		while (j < drawing->width)
		{
			drawing->draw[i][j] = drawing->c;
			j++;
		}
		drawing->draw[i][j] = 0;
		i++;
	}
	return (1);
}

void print_draw(t_drawing *drawing)
{
	int i = 0;

	while (i < drawing->height)
	{
		ft_write(drawing->draw[i]);
		write(1, "\n", 1);
		i++;
	}
}

int in_rectangle(float i, float j, t_rect *r)
{
	if (i >= r->Y && i <= r->Y + r->height && j >= r->X && j <= r->X + r->width)
		return (1);
	return (0);
}

int in_border(float i, float j,t_rect *r)
{
	if (i - r->Y < 1 || r->Y + r->height - i < 1 || j - r->X < 1 || r->X + r->width - j < 1)
		return (1);
	return (0);
}

void add_r(t_drawing *drawing, t_rect *r)
{
	float i = 0, j = 0;
	while (i < drawing->height)
	{
		j = 0;
		while (j < drawing->width)
		{
			if (in_rectangle(i, j, r) && in_border(i, j, r))
				drawing->draw[(int) i][(int) j] = r->c;
			if (r->type == 'R' && in_rectangle(i, j, r))
				drawing->draw[(int) i][(int) j] = r->c;
			j++;
		}
		i++;
	}
}

int get_rectangles(FILE *file, t_drawing *drawing)
{
	t_rect r;
	int ret = fscanf(file, "%c %f %f %f %f %c\n", &r.type, &r.X, &r.Y, &r.width, &r.height, &r.c);
	while (ret == 6)
	{
		if ((r.type != 'r' && r.type != 'R') || r.width <= 0 || r.height <= 0)
			return (0);
		add_r(drawing, &r);
		ret = fscanf(file, "%c %f %f %f %f %c\n", &r.type, &r.X, &r.Y, &r.width, &r.height, &r.c);
	}
	if (ret == -1)
		return (1);
	else
		return (0);
}

int main(int ac, char **av)
{
	FILE *file;
	t_drawing drawing;

	if (ac != 2)
		return (ft_write("Error: argument\n"));
	file = fopen(av[1], "r");
	if (!file)
		return (ft_write("Error: Operation file corrupted\n"));
	if (!get_first_line(file, &drawing))
		return (ft_write("Error: Operation file corrupted\n"));
	if (!get_rectangles(file, &drawing))
		return (ft_write("Error: Operation file corrupted\n"));
	fclose(file);
	print_draw(&drawing);
	return (0);
}
