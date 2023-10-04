/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:29:27 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 00:40:31 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


double	get_minor(t_matrix m, size_t row, size_t col);
double	cofactor(t_matrix m, size_t row, size_t col);
double	determinant(t_matrix t);
t_matrix create_submatrix(t_matrix matrix, size_t row, size_t column);


t_matrix create_submatrix(t_matrix t, size_t del_row, size_t del_col) {
    double sub_m[MATRIX_SIZE][MATRIX_SIZE];
    size_t row, col;

    row = -1;
    if (t.size == 0)
        return create_matrix(sub_m, 0);

    while (++row < t.size - 1) {
        col = -1;
        while (++col < t.size - 1) {
            sub_m[row][col] = t.elements[row + (row >= del_row)][col + (col >= del_col)];
        }
    }

    return create_matrix(sub_m, t.size - 1);
}

double determinant(t_matrix t)
{
	double det = 0;
	if (t.size == 2)
	{
		det = t.elements[0][0] * t.elements[1][1] - t.elements[0][1] * t.elements[1][0];
		return det;
	}
	size_t col = 0;
	while (col < t.size)
	{
		det += t.elements[0][col] * cofactor(t, 0, col);
		++col;
	}
	return (det);
}

double	get_minor(t_matrix m, size_t row, size_t col)
{
	double		minor;
	t_matrix	submatrix;

	submatrix = create_submatrix(m, row, col);
	minor = determinant(submatrix);
	return (minor);
}
double	cofactor(t_matrix m, size_t row, size_t col)
{
	double	cofactor;

	cofactor = get_minor(m, row, col);
	if ((row + col) % 2 != 0)
		return (-cofactor);
	return (cofactor);
}


t_matrix inverse(t_matrix matrix)
{
	double inverted[MATRIX_SIZE][MATRIX_SIZE];
    double det;
	size_t row, col;

	if (!is_invertible(matrix))
		return identity_matrix();
	det = determinant(matrix);
	row = -1;
	while(++row < matrix.size)
	{
		col = -1;
		while (++col < matrix.size)
		{
			inverted[col][row] = cofactor(matrix, row, col) / det;
		}
	}
	return create_matrix(inverted, MATRIX_SIZE);
}
