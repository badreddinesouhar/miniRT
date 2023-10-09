/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:37:41 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 08:45:18 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	rotation_z(double radians)
{
	t_matrix	result;
	double		cos_r;
	double		sin_r;

	result = identity_matrix();
	cos_r = cos(radians);
	sin_r = sin(radians);
	result.elements[0][0] = cos_r;
	result.elements[0][1] = -sin_r;
	result.elements[1][0] = sin_r;
	result.elements[1][1] = cos_r;
	return (result);
}

static t_matrix	rotation_xy(t_vector orientation)
{
	t_matrix	rotate_on_x;
	t_matrix	rotate_on_y;
	t_matrix	rotation_xy;

	rotate_on_x = rotation_x(M_PI / 2);
	rotate_on_y = rotation_y(atan(orientation.x / orientation.z));
	rotation_xy = matrix_multiply(rotate_on_y, rotate_on_x);
	return (rotation_xy);
}

static t_matrix	rotation_xz(t_vector orientation)
{
	t_matrix	rotate_x;
	t_matrix	rotate_z;
	t_matrix	rotation_xz;

	rotate_x = rotation_x(atan(orientation.z / orientation.y));
	rotate_z = rotation_z(atan(-orientation.x / orientation.y));
	rotation_xz = matrix_multiply(rotate_z, rotate_x);
	return (rotation_xz);
}

t_matrix	rotation_matrix(t_vector orientation)
{
	if (compare_float(orientation.y, 0))
		return (rotation_xy(orientation));
	return (rotation_xz(orientation));
}
