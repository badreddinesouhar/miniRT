/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_opt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:27:14 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 01:36:18 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"



double tuple_magnitude(t_tuple t)
{
    return sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2) + pow(t.w, 2));
}

t_tuple tuple_normalize(t_tuple t)
{
    double magnitude;
    t_tuple result;
    magnitude = tuple_magnitude(t);
    result.x = t.x / magnitude;
    result.y = t.y / magnitude;
    result.z = t.z / magnitude;
    result.w = t.w / magnitude;
    return result;
}

double tuple_dot(t_tuple a, t_tuple b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

t_tuple vector_cross(t_tuple a, t_tuple b) {
   t_tuple result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    result.w = 0;
    return result;
}
