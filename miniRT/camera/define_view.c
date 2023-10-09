/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:32:34 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 06:11:48 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	create_orientation(t_vector left_direction, t_vector up_direction,
		t_vector forward_direction)
{
	t_matrix	orientation;

	orientation = identity_matrix();
	orientation.elements[0][0] = left_direction.x;
	orientation.elements[0][1] = left_direction.y;
	orientation.elements[0][2] = left_direction.z;
	orientation.elements[1][0] = up_direction.x;
	orientation.elements[1][1] = up_direction.y;
	orientation.elements[1][2] = up_direction.z;
	orientation.elements[2][0] = -forward_direction.x;
	orientation.elements[2][1] = -forward_direction.y;
	orientation.elements[2][2] = -forward_direction.z;
	return (orientation);
}

t_matrix	camera_transformation(t_vector left_direction,
		t_vector up_direction, t_vector forward_direction,
		t_point camera_position)
{
	t_matrix	orientation;
	t_matrix	view_transformation;
	t_matrix	translated;

	orientation = create_orientation(left_direction, up_direction,
			forward_direction);
	translated = translation(-camera_position.x, -camera_position.y,
			-camera_position.z);
	view_transformation = matrix_multiply(orientation, translated);
	return (view_transformation);
}

t_matrix	view_transformation(t_point camera_position, t_point look_at_point,
		t_vector up_direction)
{
	t_vector	left_direction;
	t_vector	normalized_up_direction;
	t_vector	true_up_direction;

	normalized_up_direction = tuple_normalize(up_direction);
	left_direction = vector_cross(look_at_point, normalized_up_direction);
	true_up_direction = vector_cross(left_direction, look_at_point);
	return (camera_transformation(left_direction, true_up_direction,
			look_at_point, camera_position));
}
