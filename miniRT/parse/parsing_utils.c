/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:20:03 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 20:55:50 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	count_elements(char **elements)
{
	int	i;

	i = 0;
	while (elements[i])
		i++;
	return (i);
}

void	create_point_coordinates(char *line, t_point *point)
{
	char	**elements;

	elements = ft_split(line, ',');
	if (count_elements(elements) != 3)
	{
		printf("Check point argumnets\n");
		free_elements(elements);
		exit(0);
	}
	point->x = ft_atof(elements[0]);
	point->y = ft_atof(elements[1]);
	point->z = ft_atof(elements[2]);
	point->w = 1.0;
	free_elements(elements);
}

void	create_vector_coordinates(char *line, t_vector *point)
{
	char	**elements;

	elements = ft_split(line, ',');
	if (count_elements(elements) != 3)
	{
		printf("Check vector argumnets\n");
		free_elements(elements);
		exit(0);
	}
	point->x = ft_atof(elements[0]);
	point->y = ft_atof(elements[1]);
	point->z = ft_atof(elements[2]);
	point->w = 0.0;
	free_elements(elements);
}

void	set_shape_color_material(t_color color, t_shape *shape)
{
	shape->material.color = color;
}

t_color	create_parameter_color(char *elements)
{
	char	**splited;
	double	red;
	double	green;
	double	blue;

	splited = ft_split(elements, ',');
	if (count_elements(splited) != 3)
	{
		printf("Check color argumnets\n");
		free_elements(splited);
		exit(0);
	}
	red = ft_atof(splited[0]);
	green = ft_atof(splited[1]);
	blue = ft_atof(splited[2]);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
		|| blue > 255)
	{
		printf("Check color ranges argumnets\n");
		free_elements(splited);
		exit(0);
	}
	free_elements(splited);
	return (set_color(red, green, blue));
}
