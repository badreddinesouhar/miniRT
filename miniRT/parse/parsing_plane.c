/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:23:51 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 20:55:42 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	plane_mapping(t_shape *plane)
{
	t_matrix	transform;
	t_matrix	rotation;
	t_matrix	final;

	transform = translation(plane->plan.origin.x, plane->plan.origin.y,
			plane->plan.origin.z);
	rotation = rotation_matrix(plane->plan.normal);
	final = matrix_multiply(transform, rotation);
	set_transform(plane, final);
	return (0);
}

void	parse_plane(char **elements, t_minirt *s)
{
	t_shape		*plane;
	t_point		origin_point;
	t_vector	normal_vector;

	create_point_coordinates(elements[1], &origin_point);
	create_vector_coordinates(elements[2], &normal_vector);
	plane = create_plane();
	plane->plan.origin = origin_point;
	plane->plan.normal = normal_vector;
	plane->plan.color = create_parameter_color(elements[3]);
	plane_mapping(plane);
	set_shape_color_material(plane->plan.color, plane);
	ft_lstadd_back(&s->shapes, ft_lstnew(plane));
	free_elements(elements);
}
