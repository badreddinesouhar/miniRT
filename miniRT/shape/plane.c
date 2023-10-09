/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:53:54 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 21:17:04 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_shape	*create_plane(void)
{
	t_shape	*shape;

	shape = create_shape();
	shape->type = PLANE;
	shape->material.specular = 0.3;
	return (shape);
}

void	intersect_plane(t_shape *plane, t_ray ray, t_intersections **intersec)
{
	double	t;

	if (fabs(ray.direction.y) < 0.00001)
		return ;
	t = -ray.origin.y / ray.direction.y;
	sort_intersection_list(intersec, ft_lstnew(create_intersection(t, plane)));
}
