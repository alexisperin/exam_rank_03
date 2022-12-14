/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:11:42 by aperin            #+#    #+#             */
/*   Updated: 2022/12/14 19:32:43 by aperin           ###   ########.fr       */
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
		drawing->draw[i] = malloc((drawing->width + 2) * sizeof(char));
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
		drawing->draw[i][j] = '\n';
		drawing->draw[i][j + 1] = 0;
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
		i++;
	}
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
	fclose(file);
	print_draw(&drawing);
	return (0);
}
