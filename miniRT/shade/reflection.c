/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 03:16:02 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 21:09:16 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	t_vector	multply;
	t_vector	result;

	multply = tuple_multiply(normal, tuple_dot(in, normal));
	multply = tuple_multiply(multply, 2);
	result = tuple_subtract(in, multply);
	return (result);
}
