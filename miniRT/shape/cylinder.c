/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:24:59 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 21:17:00 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	interset_cap(t_shape *cylinder, t_ray ray, t_intersections **intersec)
{
	double	t;

	if (!cylinder->cylinder.closed || fabs(ray.direction.y) < 0.00001)
		return ;
	t = (cylinder->cylinder.minimum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t, cylinder->cylinder.radius) == 1)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(t,
					cylinder)));
	t = (cylinder->cylinder.maximum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t, cylinder->cylinder.radius) == 1)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(t,
					cylinder)));
}

void	intersect_cylinder_lateral(t_shape *c, t_ray _ray,
			t_intersections **intersec)
{
	t_discriminant	disc;
	double			t1;
	double			t2;
	double			y1;
	double			y2;

	disc.a = pow(_ray.direction.x, 2) + pow(_ray.direction.z, 2);
	disc.b = 2 * _ray.origin.x * _ray.direction.x + 2 * _ray.origin.z
		* _ray.direction.z;
	disc.c = pow(_ray.origin.x, 2) + pow(_ray.origin.z, 2)
		- c->cylinder.radius * c->cylinder.radius;
	disc.delta = pow(disc.b, 2) - 4 * disc.a * disc.c;
	if (disc.delta < 0)
		return ;
	t1 = (-disc.b - sqrt(disc.delta)) / (2 * disc.a);
	t2 = (-disc.b + sqrt(disc.delta)) / (2 * disc.a);
	if (t1 > t2)
		swap_double(&t1, &t2);
	y1 = _ray.origin.y + t1 * _ray.direction.y;
	if (c->cylinder.minimum < y1 && y1 < c->cylinder.maximum)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(t1, c)));
	y2 = _ray.origin.y + t2 * _ray.direction.y;
	if (c->cylinder.minimum < y2 && y2 < c->cylinder.maximum)
		sort_intersection_list(intersec, ft_lstnew(create_intersection(t2, c)));
}

void	intersect_cylinder_caps(t_shape *cylinder, t_ray _ray,
		t_intersections **intersec)
{
	cylinder->cylinder.minimum = cylinder->cylinder.origin.y
		- cylinder->cylinder.height / 2;
	cylinder->cylinder.maximum = cylinder->cylinder.origin.y
		+ cylinder->cylinder.height / 2;
	interset_cap(cylinder, _ray, intersec);
}

void	intesect_cylinder(t_shape *cylinder, t_ray _ray,
				t_intersections **intersec)
{
	intersect_cylinder_lateral(cylinder, _ray, intersec);
	intersect_cylinder_caps(cylinder, _ray, intersec);
}

t_vector	normal_at_cylinder(t_shape *cylinder,
				t_tuple point)
{
	double	dist;

	dist = point.x * point.x + point.z * point.z;
	if (dist < 1 && point.y >= cylinder->cylinder.maximum - 0.00001)
		return (vector(0, 1, 0));
	else if (dist < 1 && point.y <= cylinder->cylinder.minimum + 0.00001)
		return (vector(0, -1, 0));
	else
		return (vector(point.x, 0, point.z));
}
