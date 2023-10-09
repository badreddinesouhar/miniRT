/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:40:08 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 08:36:41 by bsouhar          ###   ########.fr       */
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

void	sort_intersection_list(t_intersections **head,
		t_intersections *new_node)
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
		s.pt = (*head);
		while (s.pt->next
			&& ((t_intersection *)(s.pt->next->content))->t <= s.intersect->t)
		{
			s.pt = s.pt->next;
			if (s.pt)
				s.head = (t_intersection *)(s.pt->content);
		}
		new_node->next = s.pt->next;
		s.pt->next = new_node;
	}
}

t_intersection	*hit(t_intersections *list)
{
	t_intersection	*intersect_head;
	t_intersections	*pt;

	if (!list)
		return (NULL);
	intersect_head = (t_intersection *)list->content;
	pt = list;
	while (pt)
	{
		if (intersect_head->t - 0.00001 > 0.0)
			return (intersect_head);
		pt = pt->next;
		if (pt)
			intersect_head = (t_intersection *)pt->content;
	}
	return (NULL);
}
