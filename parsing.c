/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 23:36:06 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/04 00:46:01 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void create_point_coordinates(char *line, t_point *point)
{
    char **elements;

    elements = ft_split(line, ',');
    point->x = ft_atof(elements[0]);
    point->y = ft_atof(elements[1]);
    point->z = ft_atof(elements[2]);
    point->w = 1.0;
}

void create_vector_coordinates(char *line, t_vector *point)
{
    char **elements;

    elements = ft_split(line, ',');
    point->x = ft_atof(elements[0]);
    point->y = ft_atof(elements[1]);
    point->z = ft_atof(elements[2]);
    point->w = 0.0;
}


t_color	create_parameter_color(char *elements)
{
	char	**splited;
	double	red;
	double	green;
	double	blue;

	splited = ft_split(elements, ',');
	red = ft_atof(splited[0]);
	green = ft_atof(splited[1]);
	blue = ft_atof(splited[2]);
	return (set_color(red, green, blue));
}

static t_light_point *create_light(char **elements, t_light_point *light)
{
    t_color point;

    // Initialize a temporary t_point structure for create_coordinates to fill.
    t_point position;

    // Call create_coordinates to populate the 'position' structure.
    create_point_coordinates(elements[1], &position);

    light->position = position;
    light->brightness = ft_atof(elements[2]);
    point = create_parameter_color(elements[3]);
    light->intensity = multiply_color_scalar(point, light->brightness);

    return light;
}

void	parse_light(char **elements, t_minirt *s)
{
	t_light_point	*light;
	t_point		position;
	t_color		intensity;

	position = point(0, 0, 0);
	intensity = create_color(1, 1, 1);
	light = create_point_light(position, intensity);
	light = create_light(elements, light);
	ft_lstadd_back(&s->lights, ft_lstnew(light));
}


void	parse_ambient(char **elements, t_minirt *s)
{
	s->ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	s->ambient->ratio = ft_atof(elements[1]);
	s->ambient->color = create_parameter_color(elements[2]);
}

void	parse_camera(char **elements, t_minirt *s)
{
	 t_point view;
	 t_vector vector;

    create_point_coordinates(elements[1], &view);
	create_vector_coordinates(elements[2], &vector);

	s->camera = (t_camera_rt *)ft_calloc(1, sizeof(t_camera));
	s->camera->point_of_view = view;
	s->camera->vector = vector;
	s->camera->field_of_view = ft_atof(elements[3]);
}



// void	set_shape_orientation_vector(t_vector vector, t_shape *shape)
// {
// 	shape->orientation = vector;
// }

void	set_shape_color_material(t_color color, t_shape *shape)
{
	shape->material.color = color;
}
static int	sphere_mapping(t_shape *sphere)
{
	t_matrix	transform;
	t_matrix	sc;
	t_matrix	final;

	transform = translation(
			sphere->sphere.origin.x,
			sphere->sphere.origin.y,
			sphere->sphere.origin.z);
	sc = scaling(
			sphere->sphere.radius,
			sphere->sphere.radius,
			sphere->sphere.radius);
	final = matrix_multiply(transform, sc);
	set_transform(sphere, final);
	return (0);
}

static int plane_mapping(t_shape *plane)
{
	t_matrix	transform;
	t_matrix	final;

	transform = translation(
			plane->plan.origin.x,
			plane->plan.origin.y,
			plane->plan.origin.z);
	final = matrix_multiply(transform, identity_matrix());
	set_transform(plane, final);
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
}

void parse_plane(char **elements, t_minirt *s)
{
	t_shape	*plane;
	t_point	origin_point;
	t_vector	normal_vector;

	create_point_coordinates(elements[1], &origin_point);
	create_vector_coordinates(elements[2], &normal_vector);
	plane = create_plane();
	plane->plan.origin = origin_point;
	plane->plan.normal = normal_vector;
	plane->plan.color = create_parameter_color(elements[3]);
	set_shape_color_material(plane->plan.color, plane);
	ft_lstadd_back(&s->shapes, ft_lstnew(plane));
}

void parse_cylinder(char **elemnts, t_minirt *s) 
{
	t_shape	*cylinder;
	t_point	origin_point;
	t_vector	normal_vector;

	create_point_coordinates(elemnts[1], &origin_point);
	create_vector_coordinates(elemnts[2], &normal_vector);
	cylinder = create_cylinder();
	cylinder->cylinder.origin = origin_point;
	cylinder->cylinder.normal = normal_vector;
	cylinder->cylinder.radius = ft_atof(elemnts[3]) / 2;
	cylinder->cylinder.height = ft_atof(elemnts[4]);
	cylinder->cylinder.color = create_parameter_color(elemnts[5]);
	set_shape_color_material(cylinder->cylinder.color, cylinder);
	ft_lstadd_back(&s->shapes, ft_lstnew(cylinder));
}

void	parse_file(char *line, t_minirt *s)
{
	char	**elements;
	int		i;

	i = 0;
	line = ft_strtrim(line, " \t");
	elements = ft_split(line, ' ');
	if (ft_strcmp(elements[0], "A") == 0)
		parse_ambient(elements, s);
	else if (ft_strcmp(elements[0], "C") == 0)
		parse_camera(elements, s);
	else if (ft_strcmp(elements[0], "L") == 0)
		parse_light(elements, s);
	else if (ft_strcmp(elements[0], "sp") == 0)
		parse_sphere(elements, s);
	else if (ft_strcmp(elements[0], "pl") == 0)
		parse_plane(elements, s);
	else if (ft_strcmp(elements[0], "cy") == 0)
		parse_cylinder(elements, s);
	else{
		printf("Error\n");
		exit(0);
	}
}

int	read_file(char *file, t_minirt *s)
{
	int		fd;
	char	*line;


	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		exit(0);
	}
	while ((line = get_next_line(fd)) > 0)
	{
		parse_file(line, s);
		// free(line);
	}

	free(line);
	close(fd);
	return (1);
}
