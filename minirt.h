/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:53:36 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/12 07:45:38 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "MLX42/include/MLX42/MLX42.h"


typedef struct s_ambient
{
    double a;
    int r;
    int g;
    int b;
} t_ambient;


typedef struct s_index
{
    double x;
    double y;
    double z; 
} t_index;

typedef struct s_cam
{
    double xc;
    double yc;
    double zc;
    double xorient;
    double yorient;
    double zorient;
    double fiview;
} t_cam;

typedef struct s_light
{
    double xl;
    double yl;
    double zl;
    double bright; 
} t_light;

typedef struct s_sp 
{
    t_index *sp_idx;
    double diam;
    int rsp;
    int gsp;
    int bsp;       
} t_sp;

typedef struct s_pl 
{
    t_index *pl_idx;
    double vx;
    double vy;
    double zy;
    int rpl;
    int gpl;
    int bpl;       
} t_pl;

typedef struct s_cy 
{
    t_index *cy_idx;
    double vx;
    double vy;
    double zy;
    double diam;
    double cy_light;
    int rscy;
    int gcy;
    int bcy;       
}   t_cy;

typedef struct s_minirt
{
    int h;
    int w;
    double t;
    t_ambient *ambient;
    t_cam *cam;
    t_light *light;
    t_pl *pl;
    t_cy *cy;
    t_sp *sp;
}   t_minirt;

int	ft_strncmp(const char *s1,const char *s2, size_t n);
char *ft_strncpy(char *s1, char *s2, int len);
char **ft_split(char *str);
int	ft_atoi(const char *str);
double	ft_atof(const char *str);
// static int	get_sign(const char *str, int *index);
// static double	parse_fraction(const char *str, int *index, int *div);
int	error_check(const char *str, int i, int sign, long nb);
int	ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void ft_putchar_fd(char c, int fd);
void init_ambient_light(char **arg, t_ambient **amb);
void init_camera(char **arg, t_cam **cam);
void init_light(char **arg, t_light **light);
void init_sp(char **arg, t_sp **sp);
void init_pl(char **arg, t_pl **pl);
void init_cy(char **arg, t_cy **cy);

#endif
