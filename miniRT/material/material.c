/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 07:02:23 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 21:02:42 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light_point	*create_point_light(t_point position, t_color intensity)
{
	t_light_point	*light;

	light = (t_light_point *)malloc(sizeof(t_light_point));
	light->position = position;
	light->intensity = intensity;
	return (light);
}

t_material	create_material(void)
{
	t_material	material;

	material.color = create_color(1, 1, 1);
	material.ambient = create_color(0.5, 0.7, 0.5);
	material.diffuse = 0.9;
	material.specular = 1.0;
	material.shininess = 200.0;
	return (material);
}

static t_vector	set_normal_object(t_shape *shape, t_point object_point)
{
	t_vector	object_normal;

	object_normal = vector(0, 0, 0);
	if (shape->type == SPHERE)
		object_normal = tuple_subtract(object_point, point(0, 0, 0));
	else if (shape->type == PLANE)
		object_normal = vector(0, 1, 0);
	else if (shape->type == CYLINDER)
		object_normal = normal_at_cylinder(shape, object_point);
	else if (shape->type == CONE)
		object_normal = normal_at_cone(shape, object_point);
	else if (shape->type == TRIANGLE)
		object_normal = normal_at_triangle(shape, object_point);
	else
		exit(0);
	return (object_normal);
}

t_vector	normal_at(t_shape *shape, t_point world_point)
{
	t_vector	world_normal;
	t_vector	object_normal;
	t_point		object_point;

	object_point = multiply_tuple_matrix(shape->inverse, world_point);
	object_normal = set_normal_object(shape, object_point);
	world_normal = multiply_tuple_matrix(shape->transpose, object_normal);
	world_normal.w = 0;
	world_normal = tuple_normalize(world_normal);
	return (world_normal);
}
