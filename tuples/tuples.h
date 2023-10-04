/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:32:53 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 01:35:15 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_H
# define TUPLES_H

#include "../minirt.h"

typedef struct {
    double x, y, z, w;
} t_tuple;

typedef t_tuple	t_point;
typedef t_tuple	t_vector;





#endif
