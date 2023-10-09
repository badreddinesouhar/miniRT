/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:04:24 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 06:10:15 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	calculate_ambient(t_lighting phong_lighting)
{
	t_color	ambient;

	ambient = multiply_color(phong_lighting.material.color,
			phong_lighting.material.ambient);
	return (ambient);
}

t_color	calculate_diffuse(t_lighting phong_lighting, t_color effect_color)
{
	t_color	diffuse;

	if (phong_lighting.light_normal < 0)
		return (create_color(0, 0, 0));
	diffuse = multiply_color_scalar(effect_color,
			phong_lighting.material.diffuse);
	diffuse = multiply_color_scalar(diffuse, phong_lighting.light_normal);
	return (diffuse);
}

t_color	calculate_specular(t_lighting phong_lighting, t_vector light_vector)
{
	t_color		specular;
	double		factor;
	t_vector	reflectv;
	double		reflect_dot_eye;

	if (phong_lighting.light_normal < 0)
		return (create_color(0, 0, 0));
	reflectv = reflect(tuple_negate(light_vector), phong_lighting.normalv);
	reflect_dot_eye = tuple_dot(reflectv, phong_lighting.eyev);
	if (reflect_dot_eye <= 0)
		return (create_color(0, 0, 0));
	factor = pow(reflect_dot_eye, phong_lighting.material.shininess);
	specular = multiply_color_scalar(phong_lighting.light_point->intensity,
			phong_lighting.material.specular);
	specular = multiply_color_scalar(specular, factor);
	return (specular);
}

t_color	combine_palettes(t_color ambient, t_color diffuse, t_color spec)
{
	t_color	result;

	result = adding_color(ambient, diffuse);
	result = adding_color(result, spec);
	return (result);
}

t_color	phong_model(t_lighting phong_lighting)
{
	t_color		effect_color;
	t_color		ambient;
	t_vector	light_vector;
	t_color		diffuse;
	t_color		specular;

	effect_color = multiply_color(phong_lighting.material.color,
			phong_lighting.light_point->intensity);
	ambient = calculate_ambient(phong_lighting);
	if (phong_lighting.in_shadow == TRUE)
		return (ambient);
	light_vector = tuple_normalize(tuple_subtract(
				phong_lighting.light_point->position, phong_lighting.position));
	phong_lighting.light_normal = tuple_dot(light_vector,
			phong_lighting.normalv);
	diffuse = calculate_diffuse(phong_lighting, effect_color);
	specular = calculate_specular(phong_lighting, light_vector);
	return (combine_palettes(ambient, diffuse, specular));
}
