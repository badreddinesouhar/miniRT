/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:28:02 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/03 19:10:05 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../minirt.h"

typedef struct s_list t_list;
typedef struct s_shape t_shape;

typedef struct s_world
{
	t_list	*light_point;
	t_list	*shapes;
}	t_world;

typedef struct s_computations
{
	t_shape		*shape;
	double		time;
	t_point		point;
	t_vector	normalv;
	t_vector	eyev;
	t_point		over_point;
}	t_computations;



t_world	*create_world(void);

/*
Function Name: intersect_world
@param t_world *world - a pointer to the world object containing shapes
@param t_ray ray - the ray to intersect with objects in the world
@param t_intersections **intersect - a pointer to a pointer for storing the resulting intersections

Description:
The intersect_world function takes a world object, a ray, and a pointer to a pointer for intersections.
It iterates through the shapes in the world, transforms the ray according to the shape's transformation
(if any), and checks for intersections between the ray and the shapes. It aggregates the intersections into
a collection and stores them in the memory location pointed to by intersect. This function allows to
find intersections between a ray and all objects in the world, providing a foundation for rendering scenes
with multiple objects.
*/

void	intersect_world(t_world *world, t_ray ray, t_intersections **intersect);

/*
Function Name: prepare_computations
@param t_intersection intersection - an intersection point between a ray and an object
@param t_ray ray - the original ray

Description:
The prepare_computations function precomputes various properties of an intersection to aid in shading
and further calculations. It takes an intersection point and the original ray as input. It computes
and stores information such as the point of intersection in world space, the eye vector
(pointing back toward the camera), and the normal vector at the intersection point.
This precomputed data is useful for various lighting and rendering calculations in later stages of ray
tracing.
*/

t_computations	prepare_computation(t_intersection *i, t_ray ray);


#endif
