/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_optn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:27:58 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/05 00:23:34 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	matrix_multiply(t_matrix A, t_matrix B)
{
	t_matrix	result;
	size_t		row;
	size_t		col;

	result.size = A.size;
	row = 0;
	while (row < A.size)
	{
		col = 0;
		while (col < A.size)
		{
			result.elements[row][col] = A.elements[row][0] * B.elements[0][col]
				+ A.elements[row][1] * B.elements[1][col] + A.elements[row][2]
				* B.elements[2][col] + A.elements[row][3] * B.elements[3][col];
			col++;
		}
		row++;
	}
	return (result);
}

t_tuple	multiply_tuple_matrix(t_matrix A, t_tuple b)
{
	t_tuple	result;

	result.x = A.elements[0][0] * b.x + A.elements[0][1] * b.y
		+ A.elements[0][2] * b.z + A.elements[0][3] * b.w;
	result.y = A.elements[1][0] * b.x + A.elements[1][1] * b.y
		+ A.elements[1][2] * b.z + A.elements[1][3] * b.w;
	result.z = A.elements[2][0] * b.x + A.elements[2][1] * b.y
		+ A.elements[2][2] * b.z + A.elements[2][3] * b.w;
	result.w = A.elements[3][0] * b.x + A.elements[3][1] * b.y
		+ A.elements[3][2] * b.z + A.elements[3][3] * b.w;
	return (result);
}

bool	is_invertible(t_matrix t)
{
	double	det;

	det = determinant(t);
	return (det != 0.0);
}
