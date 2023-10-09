/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:26:26 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/08 00:08:00 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_shape	*create_triangle(void)
{
	t_shape	*shape;

	shape = create_shape();
	shape->type = TRIANGLE;
	shape->triangle.p1 = point(0, 0, 0);
	shape->triangle.p2 = point(0, 0, 0);
	shape->triangle.p3 = point(0, 0, 0);
	shape->triangle.e1 = vector(0, 0, 0);
	shape->triangle.e2 = vector(0, 0, 0);
	shape->triangle.normal = vector(0, 0, 0);
	shape->material.specular = 0.3;
	return (shape);
}

void	smooth_triangle(t_shape *triangle, double *u, double *v)
{
	t_tuple	n1;
	t_tuple	n2;
	t_tuple	n3;

	n1 = triangle->triangle.e1;
	n2 = triangle->triangle.e2;
	n3 = triangle->triangle.normal;
	triangle->triangle.normal = tuple_add(tuple_multiply(n1, 1 - *u - *v),
			tuple_multiply(n2, *u));
	triangle->triangle.normal = tuple_add(triangle->triangle.normal,
			tuple_multiply(n3, *v));
}

void	intersect_triangle(t_shape *triangle, t_ray _ray,
		t_intersections **intersec)
{
	t_tuple			dir_cross_e2;
	t_triangle_data	data;
	t_tuple			p;
	t_tuple			origin_cross_e1;

	dir_cross_e2 = vector_cross(_ray.direction, triangle->triangle.e2);
	data.det = tuple_dot(triangle->triangle.e1, dir_cross_e2);
	if (fabs(data.det) < 0.00001)
		return ;
	data.f = 1.0 / data.det;
	p = tuple_subtract(_ray.origin, triangle->triangle.p1);
	data.u = data.f * tuple_dot(p, dir_cross_e2);
	if (data.u < 0 || data.u > 1)
		return ;
	origin_cross_e1 = vector_cross(p, triangle->triangle.e1);
	data.v = data.f * tuple_dot(_ray.direction, origin_cross_e1);
	if (data.v < 0 || (data.u + data.v) > 1)
		return ;
	data.t = data.f * tuple_dot(triangle->triangle.e2, origin_cross_e1);
	sort_intersection_list(intersec, ft_lstnew(create_intersection(data.t,
				triangle)));
}

t_vector	normal_at_triangle(t_shape *triangle, t_tuple point)
{
	(void)point;
	return (triangle->triangle.normal);
}
