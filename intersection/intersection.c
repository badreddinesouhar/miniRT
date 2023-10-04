/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:40:08 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/04 01:04:49 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


t_intersection	*create_intersection(double t, t_shape *shapes)
{
	t_intersection	*intersect;

	intersect = ft_calloc(1, sizeof(t_intersection));
	intersect->shapes = shapes;
	intersect->t = t;
	return (intersect);
}


void	sort_intersection_list(t_intersections **head, t_intersections *new_node)
{
	t_list_intersections	s; 

	s.intersect = (t_intersection *)new_node->content;
	if (*head == NULL)
		*head = new_node;
	else
	{
		s.head = (t_intersection *)(*head)->content;
		if (s.intersect->t < s.head->t)
		{
			new_node->next = *head;
			*head = new_node;
			return ;
		}
		s.point_intersected = (*head);
		while (s.point_intersected->next && ((t_intersection *)(s.point_intersected->next->content))->t <= s.intersect->t)
		{
			s.point_intersected = s.point_intersected->next;
			if (s.point_intersected)
				s.head = (t_intersection *)(s.point_intersected->content);
		}
		new_node->next = s.point_intersected->next;
		s.point_intersected->next = new_node;
	}
}


t_intersection	*hit(t_intersections *list)
{
	t_intersection	*intersect_head;
	t_intersections	*point_intersected;

	if (!list)
		return (NULL);
	intersect_head = (t_intersection *)list->content;
	point_intersected = list;
	while (point_intersected)
	{
		if (intersect_head->t - 0.00001 > 0.0)
			return (intersect_head);
		point_intersected = point_intersected->next;
		if (point_intersected)
			intersect_head = (t_intersection *)point_intersected->content;
	}
	return (NULL);
}
