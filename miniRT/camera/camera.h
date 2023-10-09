/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:33:22 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 06:11:21 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../minirt.h"

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		fov;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_matrix	transform;
	t_matrix	inverse;
}				t_camera;

t_matrix		camera_orientation(t_vector left_direction,
					t_vector up_direction, t_vector forward_direction);

t_matrix		camera(t_vector left_direction, t_vector up_direction,
					t_vector forward_direction, t_point camera_position);
t_matrix		view_transformation(t_point camera_position,
					t_point look_at_point, t_vector up_direction);

#endif
