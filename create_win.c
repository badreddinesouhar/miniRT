/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:14:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/09/23 03:39:21 by bsouhar          ###   ########.fr       */
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

double	calculate_quadra2(t_minirt *rt, double r, double x, double y, double z)
{
	double	a;
	double	b;
	double	c;
	double	dis;

	a = x * x + y * y + z * z;
	b = 2.0 * (x * rt->cam->xc + y * rt->cam->yc + z * rt->cam->zc);
	c = rt->cam->xc * rt->cam->xc + rt->cam->yc * rt->cam->yc + rt->cam->zc
		* rt->cam->zc - r * r + 1;
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
	b = (rt->light->xl * x) + (rt->light->yl * y) + (rt->light->zl * z);
	// printf("a-->%f\n", a);
	// printf("b-->%f\n", b);
	// printf("q--->%f\n", q);
	if (q == 0)
		t = -b / (2 * a);
	else if (q > 0)
		t = ((-b) - sqrt(q)) / (2 * a);
	return (t);
}
double	calculate_t(t_minirt *rt, double x, double y, double z, double q)
{
	double	t;
	double	a;
	double	b;

	t = 0.0;
	a = x * x + y * y + z * z;
	b = (rt->light->xl * x) + (rt->light->yl * y) + (rt->light->zl * z);
	// printf("a-->%f\n", a);
	// printf("b-->%f\n", b);
	// printf("q--->%f\n", q);
	if (q == 0)
		t = -b / (2 * a);
	else if (q > 0)
		t = ((-b) + sqrt(q)) / (2 * a);
	return (t);
}


int	create_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}
 
void	sphere(mlx_t *mlx, t_minirt *rt)
{
	mlx_image_t	*image;
	double		q;
	double		t;

	double x, y, z, r;
	double z1, z2;
	q = 0.0;
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
		z = z2;
			q = calculate_quadra(rt, r, x, y, z);
			if (q >= 0)
			{
				float t[] = malloc {
					(calculate_t),
					(calculate_t1),
				};
				vector3 hitposition = rayorigin + raydrection * t[i]
				vector3 normal = hitposition - vexctor3.zero;
				mlx_put_pixel(image, x, y, 0xFFFFFF);
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