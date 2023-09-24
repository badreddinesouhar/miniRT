/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:14:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/09/23 05:45:34 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"
// #define NUM_SOLUTIONS 2
// vector3 rayorigin = vector3_create(0.0, 0.0, 0.0); // Initialize with appropriate values
// vector3 raydrection = vector3_create(1.0, 0.0, 0.0); // Initialize with appropriate values

// typedef struct {
//     double x;
//     double y;
//     double z;
// } vector3;

// // Function to create a vector
// vector3 vector3_create(double x, double y, double z) {
//     vector3 v;
//     v.x = x;
//     v.y = y;
//     v.z = z;
//     return v;
// }

// // Vector addition
// vector3 vector3_add(vector3 a, vector3 b) {
//     vector3 result;
//     result.x = a.x + b.x;
//     result.y = a.y + b.y;
//     result.z = a.z + b.z;
//     return result;
// }

// // Vector scaling (multiplication by a scalar)
// vector3 vector3_scale(vector3 v, double scalar) {
//     vector3 result;
//     result.x = v.x * scalar;
//     result.y = v.y * scalar;
//     result.z = v.z * scalar;
//     return result;
// }

// // Vector subtraction
// vector3 vector3_subtract(vector3 a, vector3 b) {
//     vector3 result;
//     result.x = a.x - b.x;
//     result.y = a.y - b.y;
//     result.z = a.z - b.z;
//     return result;
// }

// // Vector zero initialization
// vector3 vector3_zero() {
//     return vector3_create(0.0, 0.0, 0.0);
// }

// vector3 vector3_normalize(vector3 v) {
//     double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
//     if (length != 0) {
//         v.x /= length;
//         v.y /= length;
//         v.z /= length;
//     }
//     return v;
// }

// // Function to multiply a vector by a scalar
// vector3 vector3_multiply(vector3 v, double scalar) {
//     v.x *= scalar;
//     v.y *= scalar;
//     v.z *= scalar;
//     return v;
// }

// double vector3_dot(vector3 a, vector3 b) {
//     return a.x * b.x + a.y * b.y + a.z * b.z;
// }

// // Function to convert a vector3 color to an integer color
// int vector3_to_color(vector3 color) {
//     // Ensure that color components are in the [0, 1] range
//     color.x = fmin(fmax(color.x, 0.0), 1.0);
//     color.y = fmin(fmax(color.y, 0.0), 1.0);
//     color.z = fmin(fmax(color.z, 0.0), 1.0);

//     // Convert each color component to an integer in the range [0, 255]
//     int red = (int)(color.x * 255);
//     int green = (int)(color.y * 255);
//     int blue = (int)(color.z * 255);

//     // Create the integer color value (RGBA format)
//     int color_value = (red << 16) | (green << 8) | blue;

//     return color_value;
// }

// int normal_to_color(vector3 normal) {
//     // Normalize the normal vector (if necessary)
//     double length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
//     normal.x /= length;
//     normal.y /= length;
//     normal.z /= length;

//     // Convert the normalized normal vector to a color value
//     int red = (int)((normal.x + 1.0) * 0.5 * 255);
//     int green = (int)((normal.y + 1.0) * 0.5 * 255);
//     int blue = (int)((normal.z + 1.0) * 0.5 * 255);

//     // Create and return the color value
//     return (red << 16) | (green << 8) | blue;
// }

// double calculate_mins(vector3 rayorigin, double r, double x, double y)
// {
//     double z;

//     z = rayorigin.z - sqrt((r * r) - (x - rayorigin.x) * (x - rayorigin.x) - (y - rayorigin.y) * (y - rayorigin.y));
//     return (z);
// }

// double calculate_plus(vector3 rayorigin, double r, double x, double y)
// {
//     double z;

//     z = rayorigin.z + sqrt((r * r) - (x - rayorigin.x) * (x - rayorigin.x) - (y - rayorigin.y) * (y - rayorigin.y));
//     return (z);
// }

// double calculate_quadra(vector3 raydirection, vector3 rayorigin, double r, double x, double y, double z)
// {
//     double a;
//     double b;
//     double c;
//     double dis;
// 	(void)raydirection;
//     a = x * x + y * y + z * z;
//     b = 2.0 * (x * rayorigin.x + y * rayorigin.y + z * rayorigin.z);
//     c = rayorigin.x * rayorigin.x + rayorigin.y * rayorigin.y + rayorigin.z * rayorigin.z - r * r;
//     dis = b * b - 4 * a * c;
//     return (dis);
// }

// double calculate_quadra2(vector3 raydirection, vector3 rayorigin, double r, double x, double y, double z)
// {
//     double a;
//     double b;
//     double c;
//     double dis;
// 	(void)raydirection;
//     a = x * x + y * y + z * z;
//     b = 2.0 * (x * rayorigin.x + y * rayorigin.y + z * rayorigin.z);
//     c = rayorigin.x * rayorigin.x + rayorigin.y * rayorigin.y + rayorigin.z * rayorigin.z - r * r + 1;
//     dis = b * b - 4 * a * c;
//     return (dis);
// }

// double calculate_t(vector3 raydirection, vector3 rayorigin, double x, double y, double z, double q, int index)
// {
//     double t;
//     double a;
//     double b;

// 	(void)rayorigin;
//     t = 0.0;
//     a = x * x + y * y + z * z;
//     b = (raydirection.x * x) + (raydirection.y * y) + (raydirection.z * z);

//     if (q == 0)
//     {
//         t = -b / (2 * a);
//     }
//     else if (q > 0)
//     {
//         // Depending on the index (0 or 1), select the appropriate solution
//         t = ((-b) + sqrt(q)) / (2 * a);
//         if (index == 0)
//         {
//             t = ((-b) - sqrt(q)) / (2 * a);
//         }
//     }
//     return t;
// }


// int	create_color(int red, int green, int blue)
// {
// 	return ((red << 16) | (green << 8) | blue);
// }

// void sphere(mlx_t *mlx, t_minirt *rt)
// {
//     mlx_image_t *image;
//     double q;

//     double x, y, z, r;
//     double z1, z2;
//     q = 0.0;
//     image = mlx_new_image(mlx, WIDTH, HEIGHT);
//     r = rt->sp->diam / 2;
//     y = 0;
//     vector3 rayorigin = vector3_create(250.0, 250.0, 250.0); // Initialize with appropriate values
//     vector3 raydirection = vector3_create(250.0, 250.0, 250.0);

//     // Define ambient light color and intensity
//     vector3 ambient_color = vector3_create(0.6, 0.6, 0.6); // Adjust intensity as needed
//     double ambient_intensity = 0.8; // Adjust intensity as needed

//     while (y < HEIGHT) {
//         x = 0;
//         while (x < WIDTH) {
//             z1 = calculate_mins(rayorigin, r, x, y);
//             z2 = calculate_plus(rayorigin, r, x, y);
//             z = z2;
//             q = calculate_quadra(raydirection, rayorigin,r, x, y, z);

//             if (q >= 0) {
//                 double t[NUM_SOLUTIONS];

//                 // Calculate the solutions
//                 for (int i = 0; i < NUM_SOLUTIONS; i++) {
//                     t[i] = calculate_t(raydirection, rayorigin, x, y, z, q, i);
//                 }

//                 // Process the solutions
//                 for (int i = 0; i < NUM_SOLUTIONS; i++) {
//                     vector3 hitposition = vector3_add(rayorigin, vector3_scale(raydirection, t[i]));

//                     // Calculate the light direction (assuming a point light source)
//                     vector3 light_position = vector3_create(0.0, 0, 0.0); // Define light position
//                     vector3 light_direction = vector3_normalize(vector3_subtract(light_position, hitposition));

//                     // Calculate the diffuse reflection
//                     vector3 normal = vector3_subtract(hitposition, vector3_zero());
//                     double diffuse_intensity = vector3_dot(normal, light_direction);
//                     diffuse_intensity = fmax(diffuse_intensity, 0.0); // Ensure non-negative value

//                     // Define light color and intensity
//                     vector3 light_color = vector3_create(0.9, 0.8, 0.2); // Adjust color as needed
//                     double light_intensity = 0.8; // Adjust intensity as needed

//                     // Calculate the diffuse reflection color
//                     vector3 diffuse_reflection = vector3_scale(vector3_multiply(light_color, light_intensity), diffuse_intensity);
					
//                     // Combine ambient and diffuse reflections
//                     vector3 ambient_reflection = vector3_scale(ambient_color, ambient_intensity);
//                     vector3 total_reflection = vector3_add(ambient_reflection, diffuse_reflection);

//                     // Apply the reflection color to the pixel
//                     int pixel_color = vector3_to_color(total_reflection);
//                     mlx_put_pixel(image, x, y, pixel_color);
//                 }
//             } else if (q < 0) {
//                 mlx_put_pixel(image, x, y, 0xFFFFFF);
//             }
//             x++;
//         }
//         y++;
//     }
//     mlx_image_to_window(mlx, image, 0, 0);
// }

// void	init_rt(t_minirt *rt)
// {
// 	mlx_t *mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);

// 	sphere(mlx, rt);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// }

#include "minirt.h"
#define NUM_SOLUTIONS 2

// Vector3 struct definition
typedef struct {
    double x;
    double y;
    double z;
} vector3;

// Function to create a vector3
vector3 vector3_create(double x, double y, double z) {
    return (vector3){x, y, z};
}

// Vector3 addition
vector3 vector3_add(vector3 a, vector3 b) {
    return (vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

// Vector3 scaling (multiplication by a scalar)
vector3 vector3_scale(vector3 v, double scalar) {
    return (vector3){v.x * scalar, v.y * scalar, v.z * scalar};
}

// Vector3 subtraction
vector3 vector3_subtract(vector3 a, vector3 b) {
    return (vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

// Vector3 zero initialization
vector3 vector3_zero() {
    return vector3_create(0.0, 0.0, 0.0);
}

// Function to multiply a vector by a scalar
vector3 vector3_multiply(vector3 v, double scalar) {
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;
    return v;
}

// Vector3 normalization
vector3 vector3_normalize(vector3 v) {
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length != 0) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
    return v;
}

// Vector3 dot product
double vector3_dot(vector3 a, vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Function to convert a vector3 color to an integer color
int vector3_to_color(vector3 color) {
    // Ensure that color components are in the [0, 1] range
    color.x = fmin(fmax(color.x, 0.0), 1.0);
    color.y = fmin(fmax(color.y, 0.0), 1.0);
    color.z = fmin(fmax(color.z, 0.0), 1.0);

    // Convert each color component to an integer in the range [0, 255]
    int red = (int)(color.x * 255);
    int green = (int)(color.y * 255);
    int blue = (int)(color.z * 255);

    // Create the integer color value (RGBA format)
    return (red << 16) | (green << 8) | blue;
}

// Function to calculate the minimum z value
double calculate_mins(vector3 rayorigin, double r, double x, double y) {
    double z = rayorigin.z - sqrt((r * r) - (x - rayorigin.x) * (x - rayorigin.x) - (y - rayorigin.y) * (y - rayorigin.y));
    return z;
}

// Function to calculate the maximum z value
double calculate_plus(vector3 rayorigin, double r, double x, double y) {
    double z = rayorigin.z + sqrt((r * r) - (x - rayorigin.x) * (x - rayorigin.x) - (y - rayorigin.y) * (y - rayorigin.y));
    return z;
}

// Function to calculate the quadratic discriminant
double calculate_quadra(vector3 rayorigin, double r, double x, double y, double z) {
    double a = x * x + y * y + z * z;
    double b = 2.0 * (x * rayorigin.x + y * rayorigin.y + z * rayorigin.z);
    double c = rayorigin.x * rayorigin.x + rayorigin.y * rayorigin.y + rayorigin.z * rayorigin.z - r * r;
    return b * b - 4 * a * c;
}

// Function to calculate t for ray-sphere intersection
double calculate_t(vector3 raydirection, double x, double y, double z, double q, int index) {
    double t = 0.0;
    double a = x * x + y * y + z * z;
    double b = (raydirection.x * x) + (raydirection.y * y) + (raydirection.z * z);

    if (q == 0) {
        t = -b / (2 * a);
    } else if (q > 0) {
        t = ((-b) + sqrt(q)) / (2 * a);
        if (index == 0) {
            t = ((-b) - sqrt(q)) / (2 * a);
        }
    }
    return t;
}

// Function to create an RGB color value
int create_color(int red, int green, int blue) {
    return (red << 16) | (green << 8) | blue;
}

void sphere(mlx_t *mlx, t_minirt *rt) {
    mlx_image_t *image;
    double q;
    double x, y, z, r;
    double z1, z2;
    q = 0.0;
    image = mlx_new_image(mlx, WIDTH, HEIGHT);
    r = rt->sp->diam / 2;
    y = 0;
    vector3 rayorigin = vector3_create(0.0, 0.0, 0.0); // Initialize with appropriate values
    vector3 raydirection = vector3_create(250.0, 250.0, 0.0);

    // Define ambient light color and intensity
    vector3 ambient_color = vector3_create(0.6, 0.6, 0.6); // Adjust intensity as needed
    double ambient_intensity = 0.8; // Adjust intensity as needed

    while (y < HEIGHT) {
        x = 0;
        while (x < WIDTH) {
            z1 = calculate_mins(rayorigin, r, x, y);
            z2 = calculate_plus(rayorigin, r, x, y);
            z = z2;
            q = calculate_quadra(rayorigin, r, x, y, z);

            if (q >= 0) {
                double t[NUM_SOLUTIONS];

                // Calculate the solutions
                for (int i = 0; i < NUM_SOLUTIONS; i++) {
                    t[i] = calculate_t(raydirection, x, y, z, q, i);
                }

                // Process the solutions
                for (int i = 0; i < NUM_SOLUTIONS; i++) {
                    vector3 hitposition = vector3_add(rayorigin, vector3_scale(raydirection, t[i]));

                    // Calculate the light direction (assuming a point light source)
                    vector3 light_position = vector3_create(400.0, 400, 400.0); // Define light position
                    vector3 light_direction = vector3_normalize(vector3_subtract(light_position, hitposition));

                    // Calculate the diffuse reflection
                    vector3 normal = vector3_subtract(hitposition, vector3_zero());
                    double diffuse_intensity = vector3_dot(normal, light_direction);
                    diffuse_intensity = fmax(diffuse_intensity, 0.0); // Ensure non-negative value

                    // Define light color and intensity
                    vector3 light_color = vector3_create(0.9, 0.8, 0.2); // Adjust color as needed
                    double light_intensity = 0.8; // Adjust intensity as needed

                    // Calculate the diffuse reflection color
                    vector3 diffuse_reflection = vector3_scale(vector3_multiply(light_color, light_intensity), diffuse_intensity);
					
                    // Combine ambient and diffuse reflections
                    vector3 ambient_reflection = vector3_scale(ambient_color, ambient_intensity);
                    vector3 total_reflection = vector3_add(ambient_reflection, diffuse_reflection);

                    // Apply the reflection color to the pixel
                    int pixel_color = vector3_to_color(total_reflection);
                    mlx_put_pixel(image, x, y, pixel_color);
                }
            } else if (q < 0) {
                mlx_put_pixel(image, x, y, 0xFFFFFF);
            }
            x++;
        }
        y++;
    }
    mlx_image_to_window(mlx, image, 0, 0);
}

void init_rt(t_minirt *rt) {
    mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
    sphere(mlx, rt);
    mlx_loop(mlx);
    mlx_terminate(mlx);
}
