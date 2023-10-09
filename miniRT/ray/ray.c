/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:40:11 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/02 01:41:09 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ray(t_point origin, t_vector direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray	new_ray;

	new_ray.origin = multiply_tuple_matrix(matrix, ray.origin);
	new_ray.direction = multiply_tuple_matrix(matrix, ray.direction);
	return (new_ray);
}

t_point	position(t_ray ray, double time)
{
	t_point	scale;
	t_point	position;

	scale = tuple_multiply(ray.direction, time);
	position = tuple_add(scale, ray.origin);
	return (position);
}

t_ray	set_ray(t_point origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	transform(t_ray ray, t_matrix matrix)
{
	t_ray		transformed_ray;
	t_point		origin;
	t_vector	direction;

	origin = multiply_tuple_matrix(matrix, ray.origin);
	direction = multiply_tuple_matrix(matrix, ray.direction);
	transformed_ray = set_ray(origin, direction);
	return (transformed_ray);
}
