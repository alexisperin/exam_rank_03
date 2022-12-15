/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:38:34 by aperin            #+#    #+#             */
/*   Updated: 2022/12/15 08:47:49 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

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

#endif