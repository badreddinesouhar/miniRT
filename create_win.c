/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:14:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/12 12:12:07 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	my_mlx_pixel_put(mlx_t *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

double calculate_mins(t_minirt *rt, double r, double x, double y)
{
    double z;
    z = rt->sp->sp_idx->z - sqrt((r * r) - (x - rt->sp->sp_idx->x) * (x - rt->sp->sp_idx->x) - (y - rt->sp->sp_idx->y) * (y - rt->sp->sp_idx->y));
    return z;
}

double calculate_plus(t_minirt *rt, double r, double x, double y)
{
    double z;
    z = rt->sp->sp_idx->z + sqrt((r * r) - (x - rt->sp->sp_idx->x) * (x - rt->sp->sp_idx->x) - (y - rt->sp->sp_idx->y) * (y - rt->sp->sp_idx->y));
    return z;
}

void sphere(mlx_t *mlx, t_minirt *rt)
{
    mlx_image_t *image;
    double x, y, z, r;
    double z1, z2;
    
    image = mlx_new_image(mlx, WIDTH, HEIGHT);

    r = rt->sp->diam / 2;
    
    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            z1 = calculate_mins(rt, r, x, y);
            z2 = calculate_plus(rt, r, x, y);
            z = z1;
            while (z <= z2)
            {
                if ((x - rt->sp->sp_idx->x)*(x - rt->sp->sp_idx->x) + (y - rt->sp->sp_idx->y)*(y - rt->sp->sp_idx->y) + (z - rt->sp->sp_idx->z)*(z - rt->sp->sp_idx->z) == r * r)
                    mlx_put_pixel(image, x, y, 0x000000);
                else 
                    mlx_put_pixel(image, x, y, 0xFFFFFF);
                z++;
            }
            y++;
        }
        x++;
    }
    
    mlx_image_to_window(mlx, image, 500, 500);
}

void init_rt(t_minirt *rt)
{
    mlx_t *mlx;
    
    mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);

    sphere(mlx, rt);

    mlx_loop(mlx);
    mlx_terminate(mlx);
}