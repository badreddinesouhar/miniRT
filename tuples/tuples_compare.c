/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_compare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:27:49 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 01:36:03 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


t_bool	compare_float(double a, double b)
{
	return (fabs(a - b) < 0.00001);
}

t_bool	compare_tuples(t_tuple a, t_tuple b)
{
	return (
		compare_float(a.x, b.x) && \
		compare_float(a.y, b.y) && \
		compare_float(a.z, b.z) && \
		compare_float(a.w, b.w)
	);
}
