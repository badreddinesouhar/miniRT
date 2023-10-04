/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:20:29 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/04 00:55:10 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_world	*create_world(void)
{
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->light_point = NULL;
	world->shapes = NULL;
	return (world);
}

void	intersect_world(t_world *world, t_ray ray, t_intersections **intersect)
{
	t_intersections	*shapes;
	t_shape			*object;
	t_ray			transformed;

	shapes = world->shapes;
	while (shapes)
	{
		object = (t_shape *)shapes->content;
		transformed = transform(ray, object->inverse);
		if (object->type == SPHERE)
			intersect_sphere(object, transformed, intersect);
		else if (object->type == PLANE)
			intersect_plane(object, transformed, intersect);
		else if (object->type == CYLINDER)
			intesect_cylinder(object, transformed, intersect);
		else
			return;
		shapes = shapes->next;
	}
}

t_computations	prepare_computation(t_intersection *i, t_ray ray)
{
	t_computations		comps;
	t_vector	vec;

	comps.time = i->t;
	comps.shape = i->shapes;
	comps.point = position(ray, comps.time);
	comps.eyev = tuple_negate(ray.direction);
	comps.normalv = normal_at(comps.shape, comps.point);
	if (tuple_dot(comps.normalv, comps.eyev) < 0)
	{
		vec = comps.normalv;
		comps.normalv = tuple_negate(comps.normalv);
	}
	vec = tuple_multiply(comps.normalv, 0.00001);
	comps.over_point = tuple_add(comps.point, vec);
	return (comps);
}
