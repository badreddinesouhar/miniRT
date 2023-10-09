/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:42:21 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 21:16:52 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	compute_cone_intersection_params(t_ray _ray, t_discriminant *disc,
		t_cone_data *data)
{
	disc->a = pow(_ray.direction.x, 2) - pow(_ray.direction.y, 2)
		+ pow(_ray.direction.z, 2);
	if (disc->a < 0.00001 && disc->b < 0.00001)
		return ;
	if (disc->a < 0.00001 && disc->b >= 0.00001)
	{
		data->t = -disc->c / (2 * disc->b);
	}
	disc->b = 2 * _ray.origin.x * _ray.direction.x - 2 * _ray.origin.y
		* _ray.direction.y + 2 * _ray.origin.z * _ray.direction.z;
	disc->c = pow(_ray.origin.x, 2) - pow(_ray.origin.y, 2) + pow(_ray.origin.z,
			2);
	disc->delta = pow(disc->b, 2) - 4 * disc->a * disc->c;
	if (disc->delta < 0)
		return ;
	data->t1 = (-disc->b - sqrt(disc->delta)) / (2 * disc->a);
	data->t2 = (-disc->b + sqrt(disc->delta)) / (2 * disc->a);
}

void	intersect_cone_lateral(t_shape *cone, t_ray _ray,
		t_intersections **intersec)
{
	t_discriminant	disc;
	t_cone_data		data;
	t_cone_data		cap_data;

	compute_cone_intersection_params(_ray, &disc, &data);
	cone->cone.minimum = cone->cone.origin.y - cone->cone.height / 2;
	cone->cone.maximum = cone->cone.origin.y + cone->cone.height / 2;
	cap_data.t1 = data.t1;
	cap_data.t2 = data.t2;
	intersect_cone_cap(cone, _ray, intersec, cap_data);
}

void	intersect_cone_caps(t_shape *cone, t_ray _ray,
		t_intersections **intersec)
{
	cone->cone.minimum = cone->cone.origin.y - cone->cone.height / 2;
	cone->cone.maximum = cone->cone.origin.y + cone->cone.height / 2;
	interset_cone_cap(cone, _ray, intersec);
}

void	intersect_cone(t_shape *cone, t_ray _ray, t_intersections **intersec)
{
	intersect_cone_lateral(cone, _ray, intersec);
	intersect_cone_caps(cone, _ray, intersec);
}

t_vector	normal_at_cone(t_shape *cone, t_tuple point)
{
	t_vector	normal;

	(void)cone;
	normal.y = sqrt(point.x * point.x + point.z * point.z);
	if (point.y > 0)
		normal.y = -normal.y;
	return (normal);
}
