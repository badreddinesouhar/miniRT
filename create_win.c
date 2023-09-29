/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:14:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/09/29 22:30:22 by bsouhar          ###   ########.fr       */
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
    double shading_factor = (normal.x + normal.y + normal.z) / 3.0; // Adjust as needed
    shading_factor = fmax(0.0, shading_factor);  // Ensure it's not negative

    int r = (int)(shading_factor * 255.0);
    int g = (int)(shading_factor * 255.0);
    int b = (int)(shading_factor * 255.0);

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

t_vector calculate_normal(t_vector orgin, t_vector hitpoint) {
	t_vector normal;
	normal.x = hitpoint.x - orgin.x;
	normal.y = hitpoint.y - orgin.y;
	normal.z = hitpoint.z - orgin.z;
	return normal;
}

int PerPixel(t_vec2 uv, mlx_image_t *image, int x, int y) {
	t_vector rayorigin = {1, 0, 2.0};
	t_vector sphereorigin = {0, 0, 0};
	t_vector raydirection = {uv.x, uv.y, -1.0};
	t_vector lightdirection = {400 , 10, 100};
	mlx_put_pixel(image, lightdirection.x, lightdirection.y, 0xFFFFFF);
	lightdirection = normalize(&lightdirection);
	double radius = 1.0;

	double a = raydirection.x * raydirection.x + raydirection.y * raydirection.y + raydirection.z * raydirection.z;
	double b = 2.0 * (raydirection.x * rayorigin.x + raydirection.y * rayorigin.y + raydirection.z * rayorigin.z);
	double c = rayorigin.x * rayorigin.x + rayorigin.y * rayorigin.y + rayorigin.z * rayorigin.z - radius * radius;
	
	
	float discriminant = b * b - 4 * a * c;
	if (discriminant >= 0.0) {
		double t[2];
		
		t[0] = (-b - sqrt(discriminant)) / (2 * a);
		t[1] = (-b + sqrt(discriminant)) / (2 * a);
		
		for (int i = 0; i < 2; i++) {			
			t_vector hitposition = {rayorigin.x + raydirection.x * t[i], rayorigin.y + raydirection.y * t[i], rayorigin.z + raydirection.z * t[i]};
			t_vector normal = calculate_normal(sphereorigin, hitposition);
			normal = normalize(&normal);
			double dot = normal.x * -lightdirection.x + normal.y * -lightdirection.y + normal.z * -lightdirection.z;
			if (dot < 0.0) {
				dot = 0.0;
			}
			mlx_put_pixel(image, x, y, create_color(
				(int)(dot * 255),
				(int)(dot * 255),
				(int)(dot * 255)
			));
		}
		return 0xFFFFFF;
	}
	mlx_put_pixel(image, x, y, 0xFFFFFF);
	return 0x000000;
}

void render(mlx_image_t	*image) {
    int m_Image_Data[HEIGHT][WIDTH];  // Declare outside the loop
	double aspectratio = (double)WIDTH / (double)HEIGHT;

	for (int y = 0; y < HEIGHT; y++) {
	    for (int x = 0; x < WIDTH; x++) {
	        t_vec2 uv = {(float)x / WIDTH, (float)y / HEIGHT};
	        uv = (t_vec2){uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0};
			uv.x *= aspectratio;
	        m_Image_Data[y][x] = PerPixel(uv, image, x, y);
			// mlx_put_pixel(image, x, y, m_Image_Data[y][x]);
	    }
	}
}

// void render(mlx_image_t *image) {
//     int m_Image_Data[HEIGHT][WIDTH];  // Declare outside the loop

//     for (int y = 0; y < HEIGHT; y++) {
//         for (int x = 0; x < WIDTH; x++) {
//             t_vec2 uv = {(float)x / WIDTH, (float)y / HEIGHT};
//             uv = (t_vec2){uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0};
//             t_vec4 raycolor = {0, 0, 0, 0};
//             m_Image_Data[y][x] = PerPixel(uv);
            
//             // Assign color components individually
//             raycolor.x = uv.x * 0.5 + 0.5;
//             raycolor.y = uv.y * 0.5 + 0.5;
//             raycolor.z = 0.5;
//             raycolor.w = 1.0;

//             // Convert and put pixel
//             mlx_put_pixel(image, x, y, create_color(
//                 (int)(raycolor.x * 255),
//                 (int)(raycolor.y * 255),
//                 (int)(raycolor.z * 255)
//             ));
//         }
//     }
// }


void	sphere(mlx_t *mlx, t_minirt *rt)
{
	mlx_image_t	*image;
	double		q;
	// double		t;

	// double x, y, z, r;
	// double z1, z2;
	q = 0.0;
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	// r = rt->sp->diam / 2;
	// y = 0;
	mlx_put_pixel(image, rt->light->xl, rt->light->yl, 0xFFFFFF);
	// while (y < HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 	z1 = calculate_mins(rt, r, x, y);
	// 	z2 = calculate_plus(rt, r, x, y);
	// 	z = z2; 
	// 		q = calculate_quadra(rt, r, x, y, z);
	// 		if (q >= 0)
	// 		{ 
	// 			double q1 = calculate_quadra_light(rt, r, x, y, z);
	// 			if (q1 >= 0) {
	// 				t_vector *point;
	// 				point = (t_vector *)malloc(sizeof(t_vector));
	// 				point->x = x;
	// 				point->y = y;
	// 				point->z = z;
	// 				t_vector normal;
	// 				normal = normal_at(rt, point);
	// 				int color = rgb_from_normal(normal);
	// 				mlx_put_pixel(image, x, y, color);
	// 				free(point);
	// 			}
	// 			else if (q1 < 0) {
	// 				// printf("q1 < 0\n");
	// 				mlx_put_pixel(image, x, y, 0xED2415);
	// 			}
	// 		}
	// 		else if (q < 0)
	// 			mlx_put_pixel(image, x, y, 0xFFFFFF);
	// 		x++;
	// 	}
	// 	y++;
	// }
	render(image);
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

// int PerPixel(t_vec2 uv) {
// 	t_vector rayorigin = {0, 0, 2.0};
// 	t_vector raydirection = {uv.x, uv.y, -1.0};
// 	double radius = 1.0;

// 	double a = raydirection.x * raydirection.x + raydirection.y * raydirection.y + raydirection.z * raydirection.z;
// 	double b = 2.0 * (raydirection.x * rayorigin.x + raydirection.y * rayorigin.y + raydirection.z * rayorigin.z);
// 	double c = rayorigin.x * rayorigin.x + rayorigin.y * rayorigin.y + rayorigin.z * rayorigin.z - radius * radius;
	
// 	float discriminant = b * b - 4 * a * c;
// 	// if (discriminant >= 0.0) {
// 	// 	return 0xFFFFFF;
// 	// }
// 	// return 0x000000;
// 	if (discriminant < 0.0) {
// 	    return 0xFFFFFF;  // Ray intersects with the sphere
// 	}
// 	return 0x000000;  // Ray doesn't intersect with the sphere
// }

// void render(mlx_image_t	*image) {
//     int m_Image_Data[HEIGHT][WIDTH];  // Declare outside the loop

// 	for (int y = 0; y < HEIGHT; y++) {
// 	    for (int x = 0; x < WIDTH; x++) {
// 	        t_vec2 uv = {(float)x / WIDTH, (float)y / HEIGHT};
// 	        uv = (t_vec2){uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0};
// 	        m_Image_Data[y][x] = PerPixel(uv);
// 			mlx_put_pixel(image, x, y, m_Image_Data[y][x]);
// 	    }
// 	}
// }

// int PerPixel(t_vec2 uv) {
// 	t_vector rayorigin = {0, 0, 2.0};
// 	t_vector raydirection = {uv.x, uv.y, -1.0};
// 	double radius = 1.0;

// 	double a = raydirection.x * raydirection.x + raydirection.y * raydirection.y + raydirection.z * raydirection.z;
// 	double b = 2.0 * (raydirection.x * rayorigin.x + raydirection.y * rayorigin.y + raydirection.z * rayorigin.z);
// 	double c = rayorigin.x * rayorigin.x + rayorigin.y * rayorigin.y + rayorigin.z * rayorigin.z - radius * radius;
	
// 	float discriminant = b * b - 4 * a * c;
// 	if (discriminant >= 0.0) {
// 		return 0xFFFFFF;
// 	}
// 	return 0x000000;
// }