/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:24:30 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/03 20:56:11 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	create_camera(double hsize, double vsize, double fov)
{
	double	half_view;
	double	aspect;
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

static t_camera	set_camera(t_camera cam, t_camera_rt *camera)
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
	transformation = view_transformation(camera->point_of_view, camera->vector, up);
	cam = set_camera_transform(cam, transformation);
	return (cam);
}
t_camera	setup_camera(t_minirt *s)
{
	t_camera	camera;

	camera = create_camera(SCREEN_WIDTH, SCREEN_WIDTH, radians(s->camera->field_of_view));
	return (set_camera(camera, s->camera));
}

static t_ray	_ray_for_pixel(t_camera camera, double x, double y)
{
	t_tuple		aux_p;
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	aux_p = point(x, y, -1);
	pixel = multiply_tuple_matrix(camera.inverse, aux_p);
	aux_p = point(0, 0, 0);
	origin = multiply_tuple_matrix(camera.inverse, aux_p);
	aux_p = tuple_subtract(pixel, origin);
	direction = tuple_normalize(aux_p);
	return (ray(origin, direction));
}

t_ray	ray_for_pixel(t_camera cam, double px, double py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;

	xoffset = (px + 0.5) * cam.pixel_size;
	yoffset = (py + 0.5) * cam.pixel_size;
	world_x = cam.half_width - xoffset;
	world_y = cam.half_height - yoffset;
	return (_ray_for_pixel(cam, world_x, world_y));
}


void	draw_on_canvas(t_camera camera, t_mlx canvas, t_world *world)
{
	size_t		x;
	size_t		y;
	t_ray		ray;
	t_color		color;

	y = 0;
	while (y < (camera.vsize - 1))
	{
		x = 0;
		while (x < (camera.hsize - 1))
		{
			ray = ray_for_pixel(camera, x, y);
			color = color_at(world, ray);
			write_pixel(canvas, x, y, color.merged);
			x++;
		}
		y++;
	}
}


t_mlx	render(t_camera camera, t_world *world)
{
	t_mlx	canvas;

	canvas = create_window(camera.vsize, camera.hsize);
	draw_on_canvas(camera, canvas, world);
	canvas.window = mlx_new_window(canvas.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	return (canvas);
}
