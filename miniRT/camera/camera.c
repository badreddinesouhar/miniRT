/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:24:30 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/08 00:45:13 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_camera	create_camera(double hsize, double vsize, double fov)
{
	double		half_view;
	double		aspect;
	t_camera	camera;

	half_view = tan(fov / 2);
	aspect = hsize / vsize;
	camera.half_width = half_view;
	camera.half_height = half_view / aspect;
	if (aspect < 1)
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / hsize;
	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.fov = fov;
	camera.transform = identity_matrix();
	camera.inverse = identity_matrix();
	return (camera);
}

t_camera	set_camera_transform(t_camera camera, t_matrix transform)
{
	camera.transform = transform;
	camera.inverse = inverse(transform);
	return (camera);
}

t_camera	set_camera(t_camera cam, t_camera_rt *camera)
{
	t_matrix	transformation;
	t_vector	aux;
	t_vector	up;

	if (compare_float(1, fabs(camera->vector.y)))
		up = (vector(1, 0, 0));
	else
	{
		aux = vector_cross(((t_tuple){0, 1, 0, 0}), camera->vector);
		up = vector_cross(camera->vector, aux);
	}
	transformation = view_transformation(camera->point_of_view, camera->vector,
			up);
	cam = set_camera_transform(cam, transformation);
	return (cam);
}

t_camera	launch_camera(t_minirt *s)
{
	t_camera	camera;

	if (!s->camera)
	{
		perror("Error: No camera found");
		exit(0);
	}
	camera = create_camera(SCREEN_WIDTH, SCREEN_WIDTH,
			radians(s->camera->field_of_view));
	return (set_camera(camera, s->camera));
}
