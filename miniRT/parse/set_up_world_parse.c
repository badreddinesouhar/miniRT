/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_world_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:25:09 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 20:55:57 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	parse_camera(char **elements, t_minirt *s)
{
	t_point		view;
	t_vector	vector;

	create_point_coordinates(elements[1], &view);
	create_vector_coordinates(elements[2], &vector);
	s->camera = (t_camera_rt *)ft_calloc(1, sizeof(t_camera));
	s->camera->point_of_view = view;
	if ((vector.x > 1 || vector.x < -1) || (vector.y > 1 || vector.y < -1)
		|| (vector.z > 1 || vector.z < -1))
	{
		printf("Check camera normalized orientation vector argumnets\n");
		free_elements(elements);
		exit(0);
	}
	s->camera->vector = vector;
	if (ft_atof(elements[3]) < 0 || ft_atof(elements[3]) > 180)
	{
		printf("Check camera field of view argumnets\n");
		free_elements(elements);
		exit(0);
	}
	s->camera->field_of_view = ft_atof(elements[3]);
	free_elements(elements);
}

void	parse_ambient(char **elements, t_minirt *s)
{
	s->ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	s->ambient->ratio = ft_atof(elements[1]);
	if (s->ambient->ratio < 0 || s->ambient->ratio > 1)
	{
		printf("Check ambient ratio argumnets\n");
		free_elements(elements);
		exit(0);
	}
	s->ambient->color = create_parameter_color(elements[2]);
	free_elements(elements);
}

t_light_point	*create_light(char **elements, t_light_point *light)
{
	t_color	point;
	t_point	position;

	create_point_coordinates(elements[1], &position);
	light->position = position;
	light->brightness = ft_atof(elements[2]);
	if (light->brightness < 0 || light->brightness > 1)
	{
		printf("Check light brightness argumnets\n");
		free_elements(elements);
		exit(0);
	}
	point = create_parameter_color(elements[3]);
	light->intensity = multiply_color_scalar(point, light->brightness);
	return (light);
}

void	parse_light(char **elements, t_minirt *s)
{
	t_light_point	*light;
	t_point			position;
	t_color			intensity;

	position = point(0, 0, 0);
	intensity = create_color(1, 1, 1);
	light = create_point_light(position, intensity);
	light = create_light(elements, light);
	ft_lstadd_back(&s->lights, ft_lstnew(light));
	free_elements(elements);
}
