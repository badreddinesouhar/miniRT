/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 07:43:40 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/15 21:42:57 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ambient_light(char **arg, t_ambient **amb)
{
	*amb = (t_ambient *)malloc(sizeof(t_ambient));
	if (*amb == NULL)
		return ;
	(*amb)->a = ft_atof(arg[1]);
	(*amb)->r = ft_atoi(arg[2]);
	(*amb)->g = ft_atoi(arg[3]);
	(*amb)->b = ft_atoi(arg[4]);
}

void	init_camera(char **arg, t_cam **cam)
{
	*cam = (t_cam *)malloc(sizeof(t_cam));
	if (*cam == NULL)
		return ;
	(*cam)->xc = ft_atof(arg[1]);
	(*cam)->yc = ft_atof(arg[2]);
	(*cam)->zc = ft_atof(arg[3]);
	(*cam)->xorient = ft_atof(arg[4]);
	(*cam)->yorient = ft_atof(arg[5]);
	(*cam)->zorient = ft_atof(arg[6]);
	(*cam)->fiview = ft_atof(arg[7]);
}

void	init_light(char **arg, t_light **light)
{
	*light = (t_light *)malloc(sizeof(t_light));
	if (*light == NULL)
		return ;
	(*light)->xl = ft_atof(arg[1]);
	(*light)->yl = ft_atof(arg[2]);
	(*light)->zl = ft_atof(arg[3]);
	(*light)->bright = ft_atof(arg[4]);
}

void	init_sp(char **arg, t_sp **sp)
{
	*sp = (t_sp *)malloc(sizeof(t_sp));
	if (*sp == NULL)
		return ;
	(*sp)->sp_idx = (t_index *)malloc(sizeof(t_index));
	if ((*sp)->sp_idx == NULL)
	{
		free(*sp);
		return ;
	}
	(*sp)->sp_idx->x = ft_atof(arg[1]);
	(*sp)->sp_idx->y = ft_atof(arg[2]);
	(*sp)->sp_idx->z = ft_atof(arg[3]);
	(*sp)->diam = ft_atof(arg[4]);
	(*sp)->rsp = ft_atoi(arg[5]);
	(*sp)->gsp = ft_atoi(arg[6]);
	(*sp)->bsp = ft_atoi(arg[7]);
}

void	init_pl(char **arg, t_pl **pl)
{
	*pl = (t_pl *)malloc(sizeof(t_pl));
	if (*pl == NULL)
		return ;
	(*pl)->pl_idx = (t_index *)malloc(sizeof(t_index));
	if ((*pl)->pl_idx == NULL)
	{
		free(*pl);
		return ;
	}
	(*pl)->pl_idx->x = ft_atof(arg[1]);
	(*pl)->pl_idx->y = ft_atof(arg[2]);
	(*pl)->pl_idx->z = ft_atof(arg[3]);
	(*pl)->vx = ft_atof(arg[4]);
	(*pl)->vy = ft_atof(arg[5]);
	(*pl)->zy = ft_atof(arg[6]);
	(*pl)->rpl = ft_atoi(arg[7]);
	(*pl)->gpl = ft_atoi(arg[8]);
	(*pl)->bpl = ft_atoi(arg[9]);
}

void	init_cy(char **arg, t_cy **cy)
{
	*cy = (t_cy *)malloc(sizeof(t_cy));
	if (*cy == NULL)
		return ;
	(*cy)->cy_idx = (t_index *)malloc(sizeof(t_index));
	if ((*cy)->cy_idx == NULL)
	{
		free(*cy);
		return ;
	}
	(*cy)->cy_idx->x = ft_atof(arg[1]);
	(*cy)->cy_idx->y = ft_atof(arg[2]);
	(*cy)->cy_idx->z = ft_atof(arg[3]);
	(*cy)->vx = ft_atof(arg[4]);
	(*cy)->vy = ft_atof(arg[5]);
	(*cy)->zy = ft_atof(arg[6]);
	(*cy)->diam = ft_atof(arg[7]);
	(*cy)->cy_light = ft_atof(arg[8]);
	(*cy)->rscy = ft_atoi(arg[9]);
	(*cy)->gcy = ft_atoi(arg[10]);
	(*cy)->bcy = ft_atoi(arg[11]);
}
