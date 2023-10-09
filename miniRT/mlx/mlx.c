/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:37:38 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/08 00:03:03 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	ft_close(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image);
	mlx_destroy_window(mlx->mlx, mlx->window);
	exit(0);
	return (0);
}

t_mlx	create_window(int height, int width)
{
	t_mlx	canvas;

	canvas.mlx = mlx_init();
	canvas.image = mlx_new_image(canvas.mlx, width, height);
	canvas.address = mlx_get_data_addr(canvas.image, &canvas.bits_per_pixel,
			&canvas.size_line, &canvas.endian);
	return (canvas);
}

void	write_pixel(t_mlx canvas, int x, int y, int color)
{
	char	*pixel;
	int		index;

	pixel = canvas.address;
	pixel += (y * canvas.size_line) + (x * (canvas.bits_per_pixel / 8));
	index = canvas.bits_per_pixel - 8;
	while (index >= 0)
	{
		if (canvas.endian == 0)
			*pixel++ = (color >> (canvas.bits_per_pixel - 8 - index)) & 0xFF;
		else
			*pixel++ = (color >> index) & 0xFF;
		index -= 8;
	}
}
