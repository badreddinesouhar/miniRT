/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 08:44:47 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 08:45:13 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	rotation_x(double radians)
{
	t_matrix	result;
	double		cos_r;
	double		sin_r;

	result = identity_matrix();
	cos_r = cos(radians);
	sin_r = sin(radians);
	result.elements[1][1] = cos_r;
	result.elements[1][2] = -sin_r;
	result.elements[2][1] = sin_r;
	result.elements[2][2] = cos_r;
	return (result);
}

t_matrix	rotation_y(double radians)
{
	t_matrix	result;
	double		cos_r;
	double		sin_r;

	result = identity_matrix();
	cos_r = cos(radians);
	sin_r = sin(radians);
	result.elements[0][0] = cos_r;
	result.elements[0][2] = sin_r;
	result.elements[2][0] = -sin_r;
	result.elements[2][2] = cos_r;
	return (result);
}
