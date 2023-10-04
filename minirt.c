/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:43:20 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/01 17:37:13 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*create_shape(void)
{
	t_shape	*shape;

	shape = (t_shape *)malloc(sizeof(t_shape));
	if (!shape)
		return (NULL);
	shape->material = create_material();
	shape->transform = identity_matrix();
	shape->transpose = identity_matrix();
	shape->inverse = identity_matrix();
	shape->orientation = vector(0, 0, 0);
	return (shape);
}

	// function to print light list :

	// void	print_lights(t_list *light)
	// {
	// 	t_light_point	*light_point;
	// 	t_light			*light_ambient;

	// 	while (light)
	// 	{
	// 		if (((t_light_point *)light->content)->position.x != 0)
	// 		{
	// 			light_point = (t_light_point *)light->content;
	// 			printf("light point position : %f %f %f\n", light_point->position.x, light_point->position.y, light_point->position.z);
	// 			printf("light point intensity : %f %f %f\n", light_point->intensity.red, light_point->intensity.green, light_point->intensity.blue);
	// 			printf("light point brightness : %f\n", light_point->brightness);
	// 		}
	// 		else
	// 		{
	// 			light_ambient = (t_light *)light->content;
	// 			printf("light ambient brightness : %f\n", light_ambient->brightness);
	// 		}
	// 		light = light->next;
	// 	}
	// }

// void print_shapes(t_list *shapes)
// {
// 	t_shape	*shape;

// 	while (shapes)
// 	{
// 		shape = (t_shape *)shapes->content;
// 		printf("shape type : %d\n", shape->type);
// 		printf("shape color : %f %f %f\n", shape->material.color.red, shape->material.color.green, shape->material.color.blue);
// 		printf("shape ambient : %f\n", shape->material.ambient);
// 		printf("shape diffuse : %f\n", shape->material.diffuse);
// 		printf("shape specular : %f\n", shape->material.specular);
// 		printf("shape shininess : %f\n", shape->material.shininess);
// 		printf("shape origin : %f %f %f\n", shape->sphere.origin.x, shape->sphere.origin.y, shape->sphere.origin.z);
// 		printf("shape radius : %f\n", shape->sphere.radius);
// 		printf("shape orientation : %f %f %f\n", shape->orientation.x, shape->orientation.y, shape->orientation.z);
// 		shapes = shapes->next;
// 	}
// }


int	main(int argc, char **argv)
{
	t_world		*world;
	t_mlx	canvas;
	t_minirt		scene;
	t_camera		camera;


	ft_bzero(&scene, sizeof(t_minirt));
	read_file(argv[1], &scene);
	world = setup_world(&scene);
	camera = setup_camera(&scene);
	canvas = render(camera, world);
	mlx_put_image_to_window(canvas.mlx, canvas.window, canvas.image, 0, 0);
	mlx_loop(canvas.mlx);
	return (0);
}

