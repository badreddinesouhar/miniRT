/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:46:30 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 21:09:23 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_lighting	init_lighting(void)
{
	t_lighting	args;

	args.light_normal = 0;
	args.position = point(0, 0, 0);
	args.shape = NULL;
	args.eyev = vector(0, 0, 0);
	args.normalv = vector(0, 0, 0);
	args.material = create_material();
	args.in_shadow = false;
	args.light_point = create_point_light(point(0, 0, 0), create_color(0, 0,
				0));
	return (args);
}

t_bool	get_shadowed(t_world *world, t_ray ray, double distance)
{
	t_intersections	*xs;
	t_intersection	*h;
	t_bool			shadow;

	xs = NULL;
	intersect_world(world, ray, &xs);
	h = hit(xs);
	shadow = (h && h->t < distance);
	ft_lstclear(&xs, free);
	return (shadow);
}

static t_bool	check(t_list *list, double distance)
{
	t_intersection	*h;

	h = hit(list);
	if (h && h->t < distance)
	{
		ft_lstclear(&list, free);
		return (TRUE);
	}
	ft_lstclear(&list, free);
	return (FALSE);
}

t_bool	is_shadowed(t_world *world, t_point p, t_light_point *light_p)
{
	t_intersections	*list;
	double			distance;
	t_vector		direction;
	t_vector		v;
	t_ray			ray_;

	list = NULL;
	v = tuple_subtract(light_p->position, p);
	distance = tuple_magnitude(v);
	direction = tuple_normalize(v);
	ray_ = ray(p, direction);
	intersect_world(world, ray_, &list);
	return (check(list, distance));
}
