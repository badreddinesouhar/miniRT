/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:24:32 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 20:55:45 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	sphere_mapping(t_shape *sphere)
{
	t_matrix	transform;
	t_matrix	sc;
	t_matrix	final;

	transform = translation(sphere->sphere.origin.x, sphere->sphere.origin.y,
			sphere->sphere.origin.z);
	sc = scaling(sphere->sphere.radius, sphere->sphere.radius,
			sphere->sphere.radius);
	final = matrix_multiply(transform, sc);
	set_transform(sphere, final);
	return (0);
}

static t_sphere	init_sphere(char **elements)
{
	t_sphere	sphere;
	t_point		origin_point;

	create_point_coordinates(elements[1], &origin_point);
	sphere.origin = origin_point;
	sphere.radius = ft_atof(elements[2]) / 2;
	sphere.color = create_parameter_color(elements[3]);
	return (sphere);
}

void	parse_sphere(char **elements, t_minirt *s)
{
	t_shape	*sphere;

	sphere = create_sphere();
	sphere->sphere = init_sphere(elements);
	sphere_mapping(sphere);
	set_shape_color_material(sphere->sphere.color, sphere);
	ft_lstadd_back(&s->shapes, ft_lstnew(sphere));
	free_elements(elements);
}
