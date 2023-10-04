/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:04:24 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/03 20:32:18 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


static t_color	get_diffuse(t_lighting args, t_color effect_color)
{
	t_color		diffuse;

	if (args.light_normal < 0)
		return (create_color(0, 0, 0));
	diffuse = multiply_color_scalar(effect_color, args.material.diffuse);
	diffuse = multiply_color_scalar(diffuse, args.light_normal);
	return (diffuse);
}

static t_color	get_specular(t_lighting args, t_vector lightv)
{
	t_color		specular;
	double		factor;
	t_vector	reflectv;
	double		reflect_dot_eye;

	if (args.light_normal < 0)
		return (create_color(0, 0, 0));
	reflectv = reflect(tuple_negate(lightv), args.normalv);
	reflect_dot_eye = tuple_dot(reflectv, args.eyev);
	if (reflect_dot_eye <= 0)
		return (create_color(0, 0, 0));
	factor = pow(reflect_dot_eye, args.material.shininess);
	specular = multiply_color_scalar(args.light_point->intensity, args.material.specular);
	specular = multiply_color_scalar(specular, factor);
	return (specular);
}

static t_color	generate_color(t_color ambient, t_color	diffuse, t_color spec)
{
	t_color	color_final;

	color_final = adding_color(ambient, diffuse);
	color_final = adding_color(color_final, spec);
	return (color_final);
}

t_color	create_lighting(t_lighting args)
{
	t_color		effect_color;
	t_vector	lightv;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;

	effect_color = multiply_color(args.material.color, args.light_point->intensity);
	ambient = multiply_color(effect_color, args.material.ambient);
	if (args.in_shadow == TRUE)
		return (ambient);
	lightv = tuple_normalize(tuple_subtract(args.light_point->position, args.position));
	args.light_normal = tuple_dot(lightv, args.normalv);
	diffuse = get_diffuse(args, effect_color);
	specular = get_specular(args, lightv);
	return (generate_color(ambient, diffuse, specular));
}
