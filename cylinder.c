/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:24:59 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/04 01:19:26 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape *create_cylinder(void) {
    t_shape *shape;

    shape = create_shape();
    shape->type = CYLINDER;
    shape->cylinder.origin = point(0, 0, 0);
    shape->cylinder.normal = vector(0, 1, 0);
    shape->cylinder.radius = 1;
    shape->cylinder.height = 1;
    shape->material.specular = 0.3;
    return (shape);
}

void intesect_cylinder(t_shape *cylinder, t_ray _ray, t_intersections **intersec) {
    t_discriminant disc;
    disc.a = pow(_ray.direction.x, 2) + pow(_ray.direction.z, 2);
    if (disc.a == 0.0)
        return ;
    disc.b = 2 * _ray.origin.x * _ray.direction.x + 2 * _ray.origin.z * _ray.direction.z;
    disc.c = pow(_ray.origin.x, 2) + pow(_ray.origin.z, 2) - 1;
    disc.delta = pow(disc.b, 2) - 4 * disc.a * disc.c;
    if (disc.delta < 0)
        return ;
    double t1 = (-disc.b - sqrt(disc.delta)) / (2 * disc.a);
    double t2 = (-disc.b + sqrt(disc.delta)) / (2 * disc.a);
    sort_intersection_list(intersec, ft_lstnew(create_intersection(t1, cylinder)));
    if (!compare_float(t1, t2))
        sort_intersection_list(intersec, ft_lstnew(create_intersection(t2, cylinder)));
}

t_vector normal_at_cylinder(t_shape *cylinder, t_tuple point) {
    t_vector normal = {point.x, 0.0, point.z};
    // t_tuple dist;
    // t_tuple temp;
    // t_tuple temp2;

    // dist = tuple_subtract(point, cylinder->cylinder.origin);
    // temp = tuple_multiply(cylinder->cylinder.normal, tuple_dot(dist, cylinder->cylinder.normal));
    // temp2 = tuple_subtract(dist, temp);
    // normal = tuple_divide(temp2, cylinder->cylinder.radius);
    return (normal);
}


// void intersect_caps(t_shape *cylinder, t_ray *_ray, t_intersections **intersec) {
//     double t;
//     t_tuple point;
//     t_tuple normal;
//     t_intersect inter;

//     if (!cylinder->cylinder.closed || fabs(_ray->direction.y) < 0.00001)
//         return ;
//     t = (cylinder->cylinder.minimum - _ray->origin.y) / _ray->direction.y;
//     point = ray_position(*_ray, t);
//     if (tuple_dot(point, point) > 1)
//         return ;
//     sort_intersection_list(intersec, ft_lstnew(create_intersection(t, cylinder)));
//     t = (cylinder->cylinder.maximum - _ray->origin.y) / _ray->direction.y;
//     point = ray_position(*_ray, t);
//     if (tuple_dot(point, point) > 1)
//         return ;
//     sort_intersection_list(intersec, ft_lstnew(create_intersection(t, cylinder)));
// }