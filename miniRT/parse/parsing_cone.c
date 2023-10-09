/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:22:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 20:55:38 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	mapping_cone(t_shape *cone)
{
	t_matrix	transform;
	t_matrix	rotation;
	t_matrix	final;

	transform = translation(cone->cone.origin.x, cone->cone.origin.y,
			cone->cone.origin.z);
	rotation = rotation_matrix(cone->cone.normal);
	final = matrix_multiply(transform, rotation);
	set_transform(cone, final);
}

void	parse_cone(char **elements, t_minirt *s)
{
	t_shape		*cone;
	t_point		origin_point;
	t_vector	normal_vector;

	create_point_coordinates(elements[1], &origin_point);
	create_vector_coordinates(elements[2], &normal_vector);
	cone = create_cone();
	cone->cone.origin = origin_point;
	cone->cone.normal = normal_vector;
	cone->cone.radius = ft_atof(elements[3]) / 2;
	cone->cone.height = ft_atof(elements[4]);
	cone->cone.color = create_parameter_color(elements[5]);
	mapping_cone(cone);
	set_shape_color_material(cone->cone.color, cone);
	ft_lstadd_back(&s->shapes, ft_lstnew(cone));
	free_elements(elements);
}
