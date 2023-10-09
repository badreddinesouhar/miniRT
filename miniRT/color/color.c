/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 03:05:02 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 21:04:29 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	new_color(double color)
{
	int	new_color;

	new_color = (int)(color * 255);
	if (new_color > 255)
		return (255);
	if (new_color < 0)
		return (0);
	return (new_color);
}

int	merge_colors(double r, double g, double b)
{
	return (new_color(r) << 16 | new_color(g) << 8 | new_color(b));
}

double	normalize_color(double color)
{
	return (color / 255.0);
}

t_color	create_color(double r, double g, double b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	color.merged = merge_colors(r, g, b);
	return (color);
}

t_color	set_color(double r, double g, double b)
{
	return (create_color(normalize_color(r), normalize_color(g),
			normalize_color(b)));
}
