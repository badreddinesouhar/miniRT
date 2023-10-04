/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:25:50 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 00:40:28 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


t_matrix create_matrix(double values[MATRIX_SIZE][MATRIX_SIZE], size_t size) {
	t_matrix result;
	result.size = size;
	for (size_t row = 0; row < size; row++) {
		for (size_t col = 0; col < size; col++) {
			result.elements[row][col] = values[row][col];
		}
	}
	return result;
}

void print_matrix(t_matrix matrix) {
	for (int row = 0; row < matrix.size; row++) {
		for (int col = 0; col < matrix.size; col++) {
			printf("%.5f\t", matrix.elements[row][col]);
		}
		printf("\n");
	}
}

t_matrix identity_matrix() {
    t_matrix identity;
    identity.size = MATRIX_SIZE;
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            if (row == col) {
                identity.elements[row][col] = 1.0;
            } else {
                identity.elements[row][col] = 0.0;
            }
        }
    }
    return identity;
}

t_matrix transpose(t_matrix A)
{
	t_matrix result;
	result.size = A.size;
	int row = 0;
	while (row < A.size)
	{
		int col = 0;
		while (col < A.size)
		{
			result.elements[row][col] = A.elements[col][row];
			col++;
		}
		row++;
	}
	return result;
}
