// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/11 12:53:32 by bsouhar           #+#    #+#             */
// /*   Updated: 2023/08/16 20:59:10 by bsouhar          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minirt.h"

int	arg_count(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}

void	fill_requirement(char **split, t_minirt *rt)
{
	if (split[0] == NULL)
		return ;
	if (!ft_strncmp(split[0], "A", 1) && arg_count(split) == 5)
		init_ambient_light(split, &rt->ambient);
	else if (!ft_strncmp(split[0], "C", 1) && arg_count(split) == 8)
		init_camera(split, &rt->cam);
	else if (!ft_strncmp(split[0], "L", 1) && arg_count(split) == 8)
		init_light(split, &rt->light);
	else if (!ft_strncmp(split[0], "pl", 2) && arg_count(split) == 10)
		init_pl(split, &rt->pl);
	else if (!ft_strncmp(split[0], "sp", 2) && arg_count(split) == 8)
		init_sp(split, &rt->sp);
	else if (!ft_strncmp(split[0], "cy", 2) && arg_count(split) == 12)
		init_cy(split, &rt->cy);
	else
		return ;
}

void	check_arg(char *arg, t_minirt *rt)
{
	char	**split;
	char *str;

	str = ft_strtrim(arg);
	if (str == NULL)
		return ;
	split = ft_split(str);
	fill_requirement(split, rt);
}

int	main(int argc, char **argv)
{
	t_minirt	*rt;
	char		*arg;
	int			fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	rt = (t_minirt *)malloc(sizeof(t_minirt));
	if (rt == NULL)
		return (1);
	while (1)
	{
		arg = get_next_line(fd);
		// add strtrim
		// if arg = =NULL
		// continue
		if (!arg)
			break ;
		check_arg(arg, rt);
		free(arg);
	}
	init_rt(rt);
	// free(rt);
	// free_all(rt);
}