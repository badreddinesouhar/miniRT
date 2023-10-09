/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:28:02 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 05:56:32 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../minirt.h"

typedef struct s_list	t_list;
typedef struct s_shape	t_shape;

typedef struct s_world
{
	t_list				*light_point;
	t_list				*shapes;
}						t_world;

typedef struct s_computations
{
	t_shape				*shape;
	double				time;
	t_point				point;
	t_vector			normalv;
	t_vector			eyev;
	t_point				over_point;
}						t_computations;

t_world					*create_world(void);

void					intersect_world(t_world *world, t_ray ray,
							t_intersections **intersect);

t_computations			prepare_computation(t_intersection *i, t_ray ray);

#endif
