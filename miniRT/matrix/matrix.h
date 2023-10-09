/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:21:32 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 06:00:21 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "../minirt.h"

# define MATRIX_SIZE 4

typedef struct s_matrix
{
	double	elements[MATRIX_SIZE][MATRIX_SIZE];
	size_t	size;
}			t_matrix;

#endif
