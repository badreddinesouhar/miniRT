/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:25:50 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/08 00:54:51 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	create_matrix(double values[MATRIX_SIZE][MATRIX_SIZE], size_t size)
{
	t_matrix	result;
	size_t		row;
	size_t		col;

	result.size = size;
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			result.elements[row][col] = values[row][col];
			col++;
		}
		row++;
	}
	return (result);
}

void	print_matrix(t_matrix matrix)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < matrix.size)
	{
		col = 0;
		while (col < matrix.size)
		{
			printf("%.5f\t", matrix.elements[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

t_matrix	identity_matrix(void)
{
	t_matrix	identity;
	size_t		row;
	size_t		col;

	identity.size = MATRIX_SIZE;
	row = 0;
	while (row < MATRIX_SIZE)
	{
		col = 0;
		while (col < MATRIX_SIZE)
		{
			if (row == col)
			{
				identity.elements[row][col] = 1.0;
			}
			else
			{
				identity.elements[row][col] = 0.0;
			}
			col++;
		}
		row++;
	}
	return (identity);
}

t_matrix	transpose(t_matrix A)
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
			result.elements[row][col] = A.elements[col][row];
			col++;
		}
		row++;
	}
	return (result);
}
