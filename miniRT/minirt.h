/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 01:16:23 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/08 08:08:10 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "get_next_line/get_next_line.h"
# include "intersection/intersection.h"
# include "matrix/matrix.h"
# include "minirt.h"
# include "tuples/tuples.h"
# include "world/world.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "ray/ray.h"

# define SCREEN_HEIGHT 800
# define SCREEN_WIDTH 800

enum				e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	TRIANGLE,
};

typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
	int		merged;
}					t_color;

typedef struct s_camera_rt
{
	t_point			point_of_view;
	t_vector		vector;
	double			field_of_view;
}					t_camera_rt;

typedef struct s_ambient
{
	double			ratio;
	t_color			color;
}					t_ambient;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	void			*image;
	char			*address;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlx;

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_sphere
{
	t_point			origin;
	float			radius;
	t_color			color;
}					t_sphere;

typedef struct s_cylinder
{
	t_point			origin;
	t_vector		normal;
	float			radius;
	float			height;
	float			minimum;
	float			maximum;
	t_color			color;
	t_bool			closed;
}					t_cylinder;

typedef struct s_data
{
	double			det;
	double			f;
	double			u;
	double			v;
	double			t;
}					t_triangle_data;

typedef struct s_triangle
{
	t_point			p1;
	t_point			p2;
	t_point			p3;
	t_vector		e1;
	t_vector		e2;
	t_vector		normal;
	t_color			color;
}					t_triangle;

typedef struct s_cone
{
	t_point			origin;
	t_vector		normal;
	float			radius;
	float			height;
	float			minimum;
	float			maximum;
	t_color			color;
	t_bool			closed;
}					t_cone;

typedef struct s_cone_data
{
	double	t;
	double	t1;
	double	t2;
	double	y1;
	double	y2;
}			t_cone_data;

typedef struct s_plane
{
	t_point			origin;
	t_vector		normal;
	t_color			color;
}					t_plane;

typedef struct s_material
{
	t_color			color;
	t_color			ambient;
	float			diffuse;
	float			specular;
	float			shininess;
}					t_material;

typedef struct s_shape
{
	enum e_type		type;
	t_sphere		sphere;
	t_plane			plan;
	t_cone			cone;
	t_triangle		triangle;
	t_cylinder		cylinder;
	t_matrix		transform;
	t_material		material;
	t_matrix		transpose;
	t_matrix		inverse;
	t_vector		orientation;
}					t_shape;

typedef struct s_light
{
	t_point			coord;
	double			brightness;
}					t_light;

typedef struct s_light_point
{
	t_point			position;
	t_color			intensity;
	double			brightness;
}					t_light_point;

typedef struct s_shearing
{
	double			xy;
	double			xz;
	double			yx;
	double			yz;
	double			zx;
	double			zy;
}					t_shearing;

typedef struct s_lighting
{
	t_light_point	*light_point;
	t_shape			*shape;
	t_vector		eyev;
	t_vector		normalv;
	t_point			position;
	t_point			over_point;
	t_material		material;
	double			light_normal;
	t_bool			in_shadow;

}					t_lighting;

typedef struct s_camera
{
	double			hsize;
	double			vsize;
	double			fov;
	double			half_width;
	double			half_height;
	double			pixel_size;
	t_matrix		transform;
	t_matrix		inverse;
}					t_camera;

typedef struct s_minirt
{
	t_ambient		*ambient;
	t_camera_rt		*camera;
	t_list			*shapes;
	t_list			*lights;

}					t_minirt;

void				free_elements(char **elements);
t_bool				compare_float(double a, double b);
t_tuple				create_tuple(double x, double y, double z, double w);
t_tuple				point(double x, double y, double z);
t_tuple				vector(double x, double y, double z);
t_tuple				tuple_add(t_tuple a, t_tuple b);
t_tuple				tuple_subtract(t_tuple a, t_tuple b);
t_tuple				tuple_negate(t_tuple t);
t_tuple				tuple_multiply(t_tuple t, double scalar);
t_tuple				tuple_divide(t_tuple t, double scalar);
t_tuple				vector_cross(t_tuple a, t_tuple b);
double				tuple_dot(t_tuple a, t_tuple b);
double				tuple_magnitude(t_tuple t);
t_tuple				tuple_normalize(t_tuple t);
t_bool				compare_tuples(t_tuple a, t_tuple b);
t_matrix			create_matrix(double values[MATRIX_SIZE][MATRIX_SIZE],
						size_t size);
void				print_matrix(t_matrix matrix);
t_matrix			identity_matrix(void);
t_matrix			matrix_multiply(t_matrix A, t_matrix B);
t_tuple				multiply_tuple_matrix(t_matrix A, t_tuple b);
t_matrix			transpose(t_matrix A);
double				get_minor(t_matrix m, size_t row, size_t col);
double				cofactor(t_matrix m, size_t row, size_t col);
double				determinant(t_matrix t);
t_matrix			get_submatrix(t_matrix matrix, size_t row, size_t column);
bool				is_invertible(t_matrix t);
t_matrix			inverse(t_matrix matrix);
t_matrix			translation(double x, double y, double z);
t_matrix			scaling(double x, double y, double z);
t_matrix			rotation_x(double radians);
t_matrix			rotation_y(double radians);
t_matrix			rotation_z(double radians);
t_matrix			shearing(t_shearing shear);
t_color				create_parameter_color(char *elements);
t_ray				ray(t_point origin, t_vector direction);
void				create_vector_coordinates(char *line, t_vector *point);
double				radians(double degree);
void				set_shape_color_material(t_color color, t_shape *shape);
t_ray				ray(t_point origin, t_vector direction);
t_ray				transform_ray(t_ray ray, t_matrix matrix);
t_point				position(t_ray ray, double time);
t_lighting			lighting(t_lighting light_attr, t_computations comps,
						t_list *light_list, t_world *world);
t_color				shade_hit(t_world *world, t_computations comps,
						t_list *light_list);
t_color				color_at(t_world *world, t_ray ray);
t_ray				set_ray(t_point origin, t_vector direction);
void				set_transform(t_shape *shapes, t_matrix transform);
t_ray				transform(t_ray ray, t_matrix matrix);
void				create_point_coordinates(char *line, t_point *point);
t_material			create_material(void);
int					merge_colors(double r, double g, double b);
double				normalize_color(double color);
t_color				create_color(double r, double g, double b);
t_color				set_color(double r, double g, double b);
t_color				adding_color(t_color a, t_color b);
t_color				sub_color(t_color a, t_color b);
t_color				multiply_color_scalar(t_color c, double mult);
t_color				multiply_color(t_color a, t_color b);
t_lighting			init_lighting(void);
t_color				phong_model(t_lighting phong_lighting);
t_bool				get_shadowed(t_world *world, t_ray ray, double distance);
t_bool				is_shadowed(t_world *world, t_point point,
						t_light_point *light_p);
t_light_point		*create_point_light(t_point position, t_color intensity);
int					count_elements(char **elements);
t_world				*create_world(void);
void				intersect_world(t_world *world, t_ray ray,
						t_intersections **intersect);
t_computations		prepare_computation(t_intersection *i, t_ray ray);
t_bool				is_shadowed(t_world *world, t_point p,
						t_light_point *light_p);
t_world				*launch_world(t_minirt *s);
t_vector			reflect(t_vector in, t_vector normal);
void				parse_camera(char **elements, t_minirt *s);
void				parse_sphere(char **elements, t_minirt *s);
t_matrix			rotation_matrix(t_vector orientation);
void				*ft_calloc(size_t count, size_t size);
void				parse_cone(char **elements, t_minirt *s);
void				parse_light(char **elements, t_minirt *s);
void				parse_plane(char **elements, t_minirt *s);
t_mlx				create_window(int height, int width);
void				write_pixel(t_mlx canvas, int x, int y, int color);
t_matrix			view_transformation(t_point camera_position,
						t_point look_at_point, t_vector up_direction);
void				parse_cylinder(char **elements, t_minirt *s);
void				ft_lstadd_front(t_list **lst, t_list *new);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strcmp(const char *s1, const char *s2);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					read_rt_file(char *file, t_minirt *s);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *str, int c, size_t len);
t_camera			create_camera(double hsize, double vsize, double fov);
t_mlx				render(t_camera camera, t_world *world);
t_camera			launch_camera(t_minirt *s);
t_vector			normal_at(t_shape *shape, t_point world_point);
double				ft_atof(const char *str);
int					ft_isdigit(char c);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
t_shape				*create_sphere(void);
char				*get_next_line(int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *str, int c);
unsigned int		ft_strlen(const char *str);
t_shape				*create_shape(void);
t_shape				*create_plane(void);
void				intersect_plane(t_shape *plane, t_ray ray,
						t_intersections **intersec);
t_vector			normal_at_cylinder(t_shape *cylinder, t_tuple point);
void				intesect_cylinder(t_shape *cylinder, t_ray _ray,
						t_intersections **intersec);
t_shape				*create_cylinder(void);
void				intersect_cone(t_shape *cone, t_ray _ray,
						t_intersections **intersec);
t_vector			normal_at_cone(t_shape *cone, t_tuple point);
t_shape				*create_cone(void);
void				interset_cone_cap(t_shape *cone, t_ray ray,
						t_intersections **intersec);
void				intersect_triangle(t_shape *triangle, t_ray _ray,
						t_intersections **intersec);
t_vector			normal_at_triangle(t_shape *triangle, t_tuple point);
t_shape				*create_triangle(void);
void				parse_triangle(char **elements, t_minirt *rt);
void				parse_ambient(char **elements, t_minirt *s);
void				swap_double(double *a, double *b);
double				check_cap(t_ray _ray, double t, double radius);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				swap_double(double *a, double *b);
double				check_cap(t_ray _ray, double t, double radius);
t_shape				*create_cone(void);
void				interset_cone_cap(t_shape *cone, t_ray ray,
						t_intersections **intersec);
void				intersect_cone_cap(t_shape *cone, t_ray _ray,
						t_intersections **intersec, t_cone_data data);
int					ft_close(t_mlx *mlx);

#endif