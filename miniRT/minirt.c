/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:43:20 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/08 00:49:59 by bsouhar          ###   ########.fr       */
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

int	key_handler(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit(0);
	}
	return (0);
}

void	free_world(t_world *world)
{
	t_list	*tmp;

	while (world->light_point)
	{
		tmp = world->light_point->next;
		free(world->light_point->content);
		free(world->light_point);
		world->light_point = tmp;
	}
	while (world->shapes)
	{
		tmp = world->shapes->next;
		free(world->shapes->content);
		free(world->shapes);
		world->shapes = tmp;
	}
	free(world);
}

void	check_basic(int ac, char **argv)
{
	if (ac != 2)
	{
		printf("Error not enought or too many arguments\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) != 0)
	{
		printf("Error \".rt\"\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_world		*world;
	t_mlx		canvas;
	t_minirt	scene;
	t_camera	camera;

	check_basic(argc, argv);
	scene.ambient = NULL;
	scene.camera = NULL;
	scene.shapes = NULL;
	scene.lights = NULL;
	read_rt_file(argv[1], &scene);
	world = launch_world(&scene);
	camera = launch_camera(&scene);
	canvas = render(camera, world);
	mlx_put_image_to_window(canvas.mlx, canvas.window, canvas.image, 0, 0);
	mlx_key_hook(canvas.window, key_handler, &canvas);
	mlx_hook(canvas.window, 17, 0, ft_close, &canvas);
	free_world(world);
	mlx_loop(canvas.mlx);
	return (0);
}
