/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:41:51 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/03 20:58:33 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"




t_lighting	lighting(t_lighting light_attr, t_computations comps, t_list *light_list, t_world *world)
{
	light_attr.eyev = comps.eyev;
	light_attr.normalv = comps.normalv;
	light_attr.position = comps.point;
	light_attr.light_point = light_list->content;
	light_attr.material = comps.shape->material;
	light_attr.in_shadow = is_shadowed(world, comps.point, light_list->content);
	light_attr.shape = comps.shape;
	return (light_attr);
}

t_color	shade_hit(t_world *world, t_computations comps, t_list *light_list)
{
	t_lighting	light_attr;
	t_color		aux[2];
	t_color		color;

	color = multiply_color(comps.shape->material.color, comps.shape->material.ambient);
	light_attr = init_lighting();
	while (light_list)
	{
		light_attr = lighting(light_attr, comps, light_list, world);
		aux[0] = color;
		aux[1] = create_lighting(light_attr);
		color = adding_color(aux[0], aux[1]);
		light_list = light_list->next;
	}
	return (color);
}

t_color	color_at(t_world *world, t_ray ray)
{
	t_intersections	*xs;
	t_intersection	*get_hit;
	t_computations			comps;
	t_color			color;

	xs = NULL;
	intersect_world(world, ray, &xs);
	get_hit = hit(xs);
	if (!get_hit)
	{
		return (create_color(0, 0, 0));
	}
	comps = prepare_computation(get_hit, ray);
	color = shade_hit(world, comps, world->light_point);
	return (color);
}

void	set_transform(t_shape *shapes, t_matrix transform)
{
	shapes->transform = transform;
	shapes->inverse = inverse(transform);
	shapes->transpose = transpose(shapes->inverse);
}
