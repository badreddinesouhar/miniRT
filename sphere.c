/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:36:40 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/01 21:43:51 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*create_sphere(void)
{
	t_shape	*shape;

	shape = create_shape();
	shape->type = SPHERE;
	shape->sphere.origin = point(0, 0, 0);
	shape->sphere.radius = 1.0;
	shape->sphere.color = set_color(255, 150, 100);
	return (shape);
}
