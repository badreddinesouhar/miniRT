/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:21:32 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 00:42:51 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H

#include "../minirt.h"


#define MATRIX_SIZE 4


typedef struct
{
    double elements[MATRIX_SIZE][MATRIX_SIZE];
	size_t size;
} t_matrix;


#endif
