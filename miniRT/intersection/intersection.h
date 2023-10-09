/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:00:49 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 08:38:12 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "../minirt.h"

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef t_list			t_intersections;
typedef struct s_shape	t_shape;
typedef struct s_ray	t_ray;

typedef struct s_intersect
{
	double				t1;
	double				t2;
	int					count;
}						t_intersect;

typedef struct s_intersection
{
	double				t;
	t_shape				*shapes;
}						t_intersection;

typedef struct s_list_intersections
{
	t_intersection		*intersect;
	t_intersections		*pt;
	t_intersection		*head;
}						t_list_intersections;

typedef struct s_discriminant
{
	double				a;
	double				b;
	double				c;
	double				delta;
}						t_discriminant;

t_intersection			*create_intersection(double t, t_shape *shapes);

void					sort_intersection_list(t_intersections **head,
							t_intersections *new_node);

t_intersection			*hit(t_intersections *list);

void					intersect_sphere(t_shape *sphere, t_ray ray,
							t_intersections **intersec);

#endif
