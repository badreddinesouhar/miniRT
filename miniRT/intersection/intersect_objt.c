/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:43:13 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 06:12:37 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	intersect_sphere(t_shape *sphere, t_ray ray, t_intersections **intersec)
{
	t_tuple			sphere_to_ray;
	t_discriminant	discriminat;
	t_intersect		inter;

	sphere_to_ray = tuple_subtract(ray.origin, point(0, 0, 0));
	discriminat.a = tuple_dot(ray.direction, ray.direction);
	discriminat.b = tuple_dot(ray.direction, sphere_to_ray) * 2;
	discriminat.c = tuple_dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminat.delta = (discriminat.b * discriminat.b) - (4 * discriminat.a
			* discriminat.c);
	if (discriminat.delta < 0)
		return ;
	inter.t1 = ((-discriminat.b - sqrt(discriminat.delta)) / (2
				* discriminat.a));
	inter.t2 = ((-discriminat.b + sqrt(discriminat.delta)) / (2
				* discriminat.a));
	sort_intersection_list(intersec, ft_lstnew(create_intersection(inter.t1,
				sphere)));
	if (!compare_float(inter.t1, inter.t2))
		sort_intersection_list(intersec, ft_lstnew(create_intersection(inter.t2,
					sphere)));
}
