/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:14:32 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 21:16:56 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	swap_double(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

double	check_cap(t_ray _ray, double t, double radius)
{
	double	x;
	double	z;

	x = _ray.origin.x + t * _ray.direction.x;
	z = _ray.origin.z + t * _ray.direction.z;
	if (x * x + z * z <= radius)
		return (1);
	else
		return (0);
}

void	intersect_cone_cap(t_shape *cone, t_ray _ray,
		t_intersections **intersec, t_cone_data data)
{
	if (data.t1 > data.t2)
		swap_double(&data.t1, &data.t2);
	data.y1 = _ray.origin.y + data.t1 * _ray.direction.y;
	if (cone->cone.minimum < data.y1 && data.y1 < cone->cone.maximum)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(data.t1,
					cone)));
	data.y2 = _ray.origin.y + data.t2 * _ray.direction.y;
	if (cone->cone.minimum < data.y2 && data.y2 < cone->cone.maximum)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(data.t2,
					cone)));
}
