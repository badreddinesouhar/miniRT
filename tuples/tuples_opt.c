/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:25:08 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 01:36:10 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple tuple_add(t_tuple a, t_tuple b)
{
    t_tuple result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

t_tuple tuple_subtract(t_tuple a, t_tuple b) {
   t_tuple result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

t_tuple tuple_negate(t_tuple t) {
    t_tuple result;
    result.x = -t.x;
    result.y = -t.y;
    result.z = -t.z;
    result.w = -t.w;
    return result;
}

t_tuple tuple_multiply(t_tuple t, double scalar) {
  t_tuple result;
    result.x = t.x * scalar;
    result.y = t.y * scalar;
    result.z = t.z * scalar;
    result.w = t.w * scalar;
    return result;
}

t_tuple tuple_divide(t_tuple t, double scalar) {
    t_tuple result;
    result.x = t.x / scalar;
    result.y = t.y / scalar;
    result.z = t.z / scalar;
    result.w = t.w / scalar;
    return result;
}
