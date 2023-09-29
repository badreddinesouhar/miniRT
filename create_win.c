/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:14:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/09/29 18:15:48 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


double	calculate_mins(t_minirt *rt, double r, double x, double y)
{
	double	z;

	z = rt->sp->sp_idx->z - sqrt((r * r) - (x - rt->sp->sp_idx->x) * (x
			- rt->sp->sp_idx->x) - (y - rt->sp->sp_idx->y) * (y
			- rt->sp->sp_idx->y));
	return (z);
}

double	calculate_plus(t_minirt *rt, double r, double x, double y)
{
	double	z;

	z = rt->sp->sp_idx->z + sqrt((r * r) - (x - rt->sp->sp_idx->x) * (x
			- rt->sp->sp_idx->x) - (y - rt->sp->sp_idx->y) * (y
			- rt->sp->sp_idx->y));
	return (z);
}

double	calculate_quadra(t_minirt *rt, double r, double x, double y, double z)
{
	double	a;
	double	b;
	double	c;
	double	dis;

	a = x * x + y * y + z * z;
	b = 2.0 * (x * rt->cam->xc + y * rt->cam->yc + z * rt->cam->zc);
	c = rt->cam->xc * rt->cam->xc + rt->cam->yc * rt->cam->yc + rt->cam->zc
		* rt->cam->zc - r * r;
	dis = b * b - 4 * a * c;
	return (dis);
}

double	calculate_quadra_light(t_minirt *rt, double r, double x, double y, double z)
{
	double	a;
	double	b;
	double	c;
	double	dis;

	a = x * x + y * y + z * z;
	b = 2.0 * (x * rt->light->xl + y * rt->light->yl + z * rt->light->zl);
	c = rt->light->xl * rt->light->xl + rt->light->yl * rt->light->yl + rt->light->zl
		* rt->light->zl - r * r;
	dis = b * b - 4 * a * c;
	return (dis);
}


double	calculate_t(t_minirt *rt, double x, double y, double z, double q)
{
	double	t;
	double	a;
	double	b;

	t = 0.0;
	a = x * x + y * y + z * z;
	b = (rt->cam->xc * x) + (rt->cam->yc * y) + (rt->cam->yc * z);
	if (q == 0)
		t = -b / (2 * a);
	else if (q > 0)
		t = ((-b) - sqrt(q)) / (2 * a);
	return (t);
}
int	create_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int rgb_from_normal(t_vector normal)
{
    int r = (int)((normal.x + 1.0) * 127.5);
    int g = (int)((normal.y + 1.0) * 127.5);
    int b = (int)((normal.z + 1.0) * 127.5);

    return (r << 16) | (g << 8) | b;
}

t_vector normalize(t_vector *v)
{
	double		len;
	t_vector	*tmp;

	tmp = (t_vector *)malloc(sizeof(t_vector));
	len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	tmp->x = v->x / len;
	tmp->y = v->y / len;
	tmp->z = v->z / len;
	return (*tmp);
}

t_vector normal_at(t_minirt *rt, t_vector *point)
{
	t_vector	normal;
	t_vector	*tmp;

	tmp = (t_vector *)malloc(sizeof(t_vector));
	tmp->x = point->x - rt->sp->sp_idx->x;
	tmp->y = point->y - rt->sp->sp_idx->y;
	tmp->z = point->z - rt->sp->sp_idx->z;
	normal = normalize(tmp);
	free(tmp);
	return (normal);
}

void	sphere(mlx_t *mlx, t_minirt *rt)
{
	mlx_image_t	*image;
	double		q;
	// double		t;

	double x, y, z, r;
	double z1, z2;
	q = 0.0;
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	r = rt->sp->diam / 2;
	y = 0;
	mlx_put_pixel(image, rt->light->xl, rt->light->yl, 0xFFFFFF);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
		z1 = calculate_mins(rt, r, x, y);
		z2 = calculate_plus(rt, r, x, y);
		z = z2; 
			q = calculate_quadra(rt, r, x, y, z);
			if (q >= 0)
			{ 
				double q1 = calculate_quadra_light(rt, r, x, y, z);
				if (q1 >= 0) {
					t_vector *point;
					point = (t_vector *)malloc(sizeof(t_vector));
					point->x = x;
					point->y = y;
					point->z = z;
					t_vector normal;
					normal = normal_at(rt, point);
					int color = rgb_from_normal(normal);
					mlx_put_pixel(image, x, y, color);
					free(point);
				}
				else if (q1 < 0) {
					// printf("q1 < 0\n");
					mlx_put_pixel(image, x, y, 0xFFFFFF);
				}
			}
			else if (q < 0)
				mlx_put_pixel(image, x, y, 0xED2415);
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, image, 0, 0);
}

void	init_rt(t_minirt *rt)
{
	mlx_t *mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);

	sphere(mlx, rt);

	mlx_loop(mlx);
	mlx_terminate(mlx);
}