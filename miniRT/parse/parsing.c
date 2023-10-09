/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 04:51:39 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/08 00:47:43 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	parse_element(char **elements, t_minirt *s)
{
	if (ft_strcmp(elements[0], "A") == 0 && count_elements(elements) == 3)
		parse_ambient(elements, s);
	else if (ft_strcmp(elements[0], "C") == 0 && count_elements(elements) == 4)
		parse_camera(elements, s);
	else if (ft_strcmp(elements[0], "L") == 0 && count_elements(elements) == 4)
		parse_light(elements, s);
	else if (ft_strcmp(elements[0], "sp") == 0 && count_elements(elements) == 4)
		parse_sphere(elements, s);
	else if (ft_strcmp(elements[0], "pl") == 0 && count_elements(elements) == 4)
		parse_plane(elements, s);
	else if (ft_strcmp(elements[0], "cy") == 0 && count_elements(elements) == 6)
		parse_cylinder(elements, s);
	else if (ft_strcmp(elements[0], "cn") == 0 && count_elements(elements) == 6)
		parse_cone(elements, s);
	else if (ft_strcmp(elements[0], "tr") == 0 && count_elements(elements) == 5)
		parse_triangle(elements, s);
	else
		return (0);
	return (1);
}

void	parse_file(char *line, t_minirt *s)
{
	char	**elements;

	elements = ft_split(line, ' ');
	free(line);
	if (count_elements(elements) == 1)
	{
		free_elements(elements);
		return ;
	}
	if (!parse_element(elements, s))
	{
		perror("ERROR FOUND");
		exit(0);
	}
}

int	open_rt_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR FOUND");
		exit(0);
	}
	return (fd);
}

int	read_rt_file(char *file, t_minirt *s)
{
	int		fd;
	char	*line;

	fd = open_rt_file(file);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line = ft_strtrim(line, " \v\t\r");
		if (!line || *line == '\n' || *line == '#')
		{
			free(line);
			continue ;
		}
		parse_file(line, s);
	}
	close(fd);
	return (1);
}
