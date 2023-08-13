/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:14:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/13 10:15:27 by bsouhar          ###   ########.fr       */
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

double calculate_quadra(t_minirt *rt, double r, double x, double y, double z)
{
    double a = x * x + y * y + z * z;
    double b = 2.0 * (x * rt->cam->xc + y * rt->cam->yc + z * rt->cam->zc);
    double c = rt->cam->xc * rt->cam->xc + rt->cam->yc * rt->cam->yc +
               rt->cam->zc * rt->cam->zc - r * r;

    double discriminant = b * b - 4 * a * c;
    return discriminant;
}


double calculate_t(t_minirt *rt, double x, double y, double z, double q)
{
    double t = 0.0;

    double a = x * x + y * y + z * z;
    double b = (rt->light->xl * x) + (rt->light->yl * y) + (rt->light->zl * z);

    if (q == 0)
        t = -b / (2 * a);
    else if (q > 0)
        t = ((-b) - sqrt(q)) / (2 * a);
    return t;
}

int create_color(int red, int green, int blue)
 {
    return (red << 16) | (green << 8) | blue;
 }

void sphere(mlx_t *mlx, t_minirt *rt)
{
    mlx_image_t *image;
    double x, y, z, r;
    double z1, z2;
    double q = 0.0;
    double t = 0.0;
    
    image = mlx_new_image(mlx, WIDTH, HEIGHT);

    r = rt->sp->diam / 2;
    
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            z1 = calculate_mins(rt, r, x, y);
            z2 = calculate_plus(rt, r, x, y);
            z = z1;
            while (z <= z2)
            {
                q = calculate_quadra(rt, r, x, y, z);
                if (q > 0)
                {
                    t = calculate_t(rt, x, y, z, q);
                    double nx = (x + t * rt->cam->xc - rt->sp->sp_idx->x) / r;
                    double ny = (y + t * rt->cam->yc - rt->sp->sp_idx->y) / r;
                    double nz = (z + t * rt->cam->zc - rt->sp->sp_idx->z) / r;
                    // double dot_product = nx * rt->light->xl + ny * rt->light->yl + nz * rt->light->zl;
                    int color_value = (int)(1);
                    mlx_put_pixel(image, x, y, create_color(color_value, color_value, color_value));
                }
                else if (q < 0)
                    mlx_put_pixel(image, x, y, 0xFFFFFF);
                z++;
            }
            x++;
        }
        y++;
    }
    
    mlx_image_to_window(mlx, image, 0, 0);
}


void init_rt(t_minirt *rt)
{
    mlx_t *mlx;
    
    mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);

    sphere(mlx, rt);

    mlx_loop(mlx);
    mlx_terminate(mlx);
}