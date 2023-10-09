/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 08:53:04 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 21:11:48 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	draw_ray(t_camera camera, double x, double y)
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
	return (draw_ray(cam, world_x, world_y));
}

void	draw_on_canvas(t_camera camera, t_mlx canvas, t_world *world)
{
	size_t	x;
	size_t	y;
	t_ray	ray;
	t_color	color;

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
	canvas.window = mlx_new_window(canvas.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"miniRT");
	return (canvas);
}
