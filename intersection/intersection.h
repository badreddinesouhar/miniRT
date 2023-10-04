/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:00:49 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/01 21:47:51 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
#include "../minirt.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;


typedef t_list	t_intersections;
typedef struct  s_shape t_shape;
typedef struct s_ray t_ray;

/*
t_intersect : struct represents an intersection result between a ray and a shape.
@param t1: A parameter representing one of the intersection points along the ray.
@param t2: A parameter representing another intersection point along the ray.
@param count: A count of the number of intersections found.
*/

typedef struct s_intersect
{
	double	t1;
	double	t2;
	int		count;
}	t_intersect;

/*
Struct s_intersection: Tracking Intersections between rays and various geometric
shapes in complex scenes. It addresses the challenge of understanding what was
intersected at a given point and gathering essential details about it.

@param t:the location along the ray where the intersection occurred. It provides a way
 to measure the distance from the ray's origin to the intersection point.

@param *shapes: pointer to the shape or object that was intersected. It connects the
intersection to the specific object within the scene, allowing you to access its properties
such as color, material, and more.

*/

typedef struct s_intersection
{
	double	t;
	t_shape	*shapes;
}	t_intersection;

/*
Struct s_list_intersections: Managing Intersection Lists

@param : intersect (t_intersection): pointer to a t_intersection structure, which typically
contains data about a specific intersection . It represents an individual intersection point
between a ray and an object within the scene.

@param : point_intersected (t_intersections): pointer to a t_intersections structure  . In a
 more complexscene, a single point may have multiple intersections with various objects. This
member helps group and manage these intersections.

@param : head (t_intersection):pointer to a t_intersection structure. It typically points to
the first intersection in a list of intersections. In the context of ray-object intersection
 management, this "head" intersection often represents the first or closest intersection along
the ray's path.
*/

typedef struct s_list_intersections
{
	t_intersection	*intersect;
	t_intersections	*point_intersected;
	t_intersection	*head;
}	t_list_intersections;

/*
Struct s_discriminant: Computing Intersection Discriminant with a sphere in a 3D scene. I

@param a (double):It quantifies the magnitude and direction of the ray.
@param b (double): helps account for the relationship between the ray and the sphere's center.
@param c (double): It characterizes the distance between the ray's origin and the sphere's center.
@param delta (double):holds the computed discriminant value, which plays a central role in determining
whethe r an intersection occurs between the ray and the sphere.  If the discriminant is
negative (discriminant < 0), it signifies that the ray does not intersect with the sphere, and no
intersections occur between them. Conversely, if the discriminant is non-negative, it indicates that
the ray intersects with the sphere.
*/

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	delta;
}	t_discriminant;


/*
create_intersection: function creates an intersection record list which is essential
because a ray can intersect multiple objects in a complex scene
*/

t_intersection	*create_intersection(double t, t_shape *shapes);

/*
sort_intersection_list: function adds a new intersection record to a sorted list of intersections .
Sorting these intersections helps determine the closest visible intersection (hit), and hits are
crucial for rendering the visible objects accurately.
*/

void	sort_intersection_list(t_intersections **head, t_intersections *new_node);

/*
hit: function identifies the hit (visible) intersection from a collection of intersection records by
through the intersection list to find the hit, which is the intersection with the lowestnonnegative t
value allowing us to determine the color, material, and properties of the object that the ray hits
*/

t_intersection	*hit(t_intersections *list);

/*
intersect_sphere:  function calculates the intersections between a ray and a sphere and stores the
intersection records in a list for further processing.
*/

void	intersect_sphere(t_shape *sphere, t_ray ray, t_intersections **intersec);

#endif
