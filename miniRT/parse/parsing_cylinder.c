/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:23:03 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 20:55:40 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_shape	*create_cylinder(void)
{
	t_shape	*shape;

	shape = create_shape();
	shape->type = CYLINDER;
	shape->cylinder.origin = point(0, 0, 0);
	shape->cylinder.normal = vector(0, 1, 0);
	shape->cylinder.minimum = -INFINITY;
	shape->cylinder.maximum = INFINITY;
	shape->material.specular = 0.3;
	shape->cylinder.closed = TRUE;
	return (shape);
}

void	mapping_cylinder(t_shape *cylinder)
{
	t_matrix	transform;
	t_matrix	rotation;
	t_matrix	final;

	transform = translation(cylinder->cylinder.origin.x,
			cylinder->cylinder.origin.y, cylinder->cylinder.origin.z);
	rotation = rotation_matrix(cylinder->cylinder.normal);
	final = matrix_multiply(transform, rotation);
	set_transform(cylinder, final);
}

void	parse_cylinder(char **elements, t_minirt *s)
{
	t_shape		*cylinder;
	t_point		origin_point;
	t_vector	normal_vector;

	create_point_coordinates(elements[1], &origin_point);
	create_vector_coordinates(elements[2], &normal_vector);
	cylinder = create_cylinder();
	cylinder->cylinder.origin = origin_point;
	cylinder->cylinder.normal = normal_vector;
	cylinder->cylinder.radius = ft_atof(elements[3]) / 2;
	cylinder->cylinder.height = ft_atof(elements[4]);
	cylinder->cylinder.color = create_parameter_color(elements[5]);
	mapping_cylinder(cylinder);
	set_shape_color_material(cylinder->cylinder.color, cylinder);
	ft_lstadd_back(&s->shapes, ft_lstnew(cylinder));
	free_elements(elements);
}
