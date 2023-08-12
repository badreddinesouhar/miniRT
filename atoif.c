/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 06:50:25 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/12 06:56:33 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	error_check(const char *str, int i, int sign, long nb)
{
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		nb = (nb * 10) + (str[i] - '0');
		if (nb < INT_MIN || nb > INT_MAX)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		i++;
	}
	nb = (nb * sign);
	return (nb);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	long	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (error_check(str, i, sign, nb));
}

static double	parse_fraction(const char *str, int *index, int *div)
{
	double	res;
	int		i;

	res = 0.0;
	i = *index;
	*div = 1;
	while (ft_isdigit(str[i]))
	{
		res = res * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			res = res * 10.0 + (str[i] - '0');
			*div *= 10;
			i++;
		}
	}
	*index = i;
	return (res);
}

static int	get_sign(const char *str, int *index)
{
	int	sign;

	sign = 1;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			sign = -1;
		(*index)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	int		i;
	double	sign;
	double	res;
	int		div;

	i = 0;
	sign = 1.0;
	res = 0.0;
	div = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = get_sign(str, &i);
	res = parse_fraction(str, &i, &div);
	return (sign * res / div);
}
