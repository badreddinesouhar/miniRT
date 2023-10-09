/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 08:55:27 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 21:04:26 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	adding_color(t_color a, t_color b)
{
	t_color	new_color;

	new_color = create_color(a.red + b.red, a.green + b.green, a.blue + b.blue);
	return (new_color);
}

t_color	sub_color(t_color a, t_color b)
{
	t_color	new_color;

	new_color = create_color(a.red - b.red, a.green - b.green, a.blue - b.blue);
	return (new_color);
}

t_color	multiply_color_scalar(t_color c, double mult)
{
	t_color	new_color;

	new_color = create_color(c.red * mult, c.green * mult, c.blue * mult);
	return (new_color);
}

t_color	multiply_color(t_color a, t_color b)
{
	t_color	new_color;

	new_color = create_color(a.red * b.red, a.green * b.green, a.blue * b.blue);
	return (new_color);
}
