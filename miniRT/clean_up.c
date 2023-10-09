/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 05:46:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 05:46:38 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_elements(char **elements)
{
	int	i;

	i = 0;
	if (elements)
	{
		while (elements[i])
		{
			free(elements[i]);
			elements[i] = NULL;
			i++;
		}
		free(elements);
	}
	elements = NULL;
}
