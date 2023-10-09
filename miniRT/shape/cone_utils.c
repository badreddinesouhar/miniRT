/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:27:51 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 21:16:36 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_shape	*create_cone(void)
{
	t_shape	*shape;

	shape = create_shape();
	shape->type = CONE;
	shape->cone.closed = TRUE;
	return (shape);
}

void	interset_cone_cap(t_shape *cone, t_ray ray, t_intersections **intersec)
{
	double	t;

	if (!cone->cone.closed || fabs(ray.direction.y) < 0.00001)
		return ;
	t = (cone->cone.minimum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t, cone->cone.radius) == 1)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(t,
					cone)));
	t = (cone->cone.maximum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t, cone->cone.radius) == 1)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(t,
					cone)));
}
