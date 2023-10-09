/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:21:40 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 20:55:47 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	mapping_triangle(t_shape *triangle)
{
	t_matrix	transform;
	t_matrix	final;

	transform = translation(triangle->triangle.p1.x, triangle->triangle.p1.y,
			triangle->triangle.p1.z);
	final = matrix_multiply(transform, identity_matrix());
	set_transform(triangle, final);
}

void	parse_triangle(char **elements, t_minirt *rt)
{
	t_shape	*triangle;

	triangle = create_triangle();
	create_point_coordinates(elements[1], &triangle->triangle.p1);
	create_point_coordinates(elements[2], &triangle->triangle.p2);
	create_point_coordinates(elements[3], &triangle->triangle.p3);
	triangle->triangle.e1 = tuple_subtract(triangle->triangle.p2,
			triangle->triangle.p1);
	triangle->triangle.e2 = tuple_subtract(triangle->triangle.p3,
			triangle->triangle.p1);
	triangle->triangle.normal = tuple_normalize(vector_cross(
				triangle->triangle.e2, triangle->triangle.e1));
	triangle->triangle.color = create_parameter_color(elements[4]);
	mapping_triangle(triangle);
	set_shape_color_material(triangle->triangle.color, triangle);
	ft_lstadd_back(&rt->shapes, ft_lstnew(triangle));
	free_elements(elements);
}
