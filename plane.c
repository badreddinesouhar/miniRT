/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:53:54 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/03 22:57:07 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_shape	*create_plane(void)
{
	t_shape	*shape;

	shape = create_shape();
	shape->type = PLANE;
	// shape->plan.origin = point(0, 0, 0);
    // shape->plan.normal = vector(0, 1, 0);
	// shape->plan.color = set_color(0, 150, 0);
    shape->material.specular = 0.3;
	return (shape);
}

void	intersect_plane(t_shape *plane, t_ray ray, t_intersections **intersec)
{
    double t;

    if (fabs(ray.direction.y) < 0.00001)
        return ;
    t = -ray.origin.y / ray.direction.y;
    sort_intersection_list(intersec, ft_lstnew(create_intersection(t, plane)));
}
