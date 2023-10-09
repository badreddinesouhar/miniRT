/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 00:21:43 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 20:58:42 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	radians(double degree)
{
	return ((degree / 180) * M_PI);
}

void	set_lights(t_list **light, t_minirt *s)
{
	*light = s->lights;
}

void	set_shape_material(t_shape *shape, t_minirt *s)
{
	shape->material.ambient = multiply_color_scalar(s->ambient->color,
			s->ambient->ratio);
}

void	set_shapes(t_list **shapes, t_minirt *s)
{
	t_shape	*current_shape;
	t_list	*shape_list;

	shape_list = s->shapes;
	while (shape_list)
	{
		current_shape = (t_shape *)shape_list->content;
		set_shape_material(current_shape, s);
		shape_list = shape_list->next;
	}
	*shapes = s->shapes;
}

t_world	*launch_world(t_minirt *s)
{
	t_world	*world;

	world = create_world();
	set_shapes(&world->shapes, s);
	set_lights(&world->light_point, s);
	return (world);
}
