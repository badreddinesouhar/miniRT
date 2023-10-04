/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:36:23 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 00:40:46 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix translation(double x, double y, double z)
{
	t_matrix result;
	result = identity_matrix();
	result.elements[0][3] = x;
	result.elements[1][3] = y;
	result.elements[2][3] = z;
	return result;
}

t_matrix scaling(double x, double y, double z)
{
	t_matrix result;
	result = identity_matrix();
	result.elements[0][0] = x;
	result.elements[1][1] = y;
	result.elements[2][2] = z;
	return result;
}

t_matrix shearing(t_shearing shear)
{
	t_matrix result;

	result = identity_matrix();
	result.elements[0][1] = shear.xy;
	result.elements[0][2] = shear.xz;
	result.elements[1][0] = shear.yx;
	result.elements[1][2] = shear.yz;
	result.elements[2][0] = shear.zx;
	result.elements[2][1] = shear.zy;
	return (result);
}
