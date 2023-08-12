/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 06:35:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/12 06:44:56 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strncmp(const char *s1,const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char *ft_strncpy(char *s1, char *s2, int len)
{
    int i;
    i = 0;
    
    while (i < len && s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
    return (s1);
}

char **ft_split(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int wc = 0;

    while (str[i] != '\0')
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == ','))
            i++;
        if (str[i])
            wc++;
        while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != ','))
            i++;
    }
    char **split = (char **)malloc(sizeof (char *) * wc + 1);
    if (!split)
        return NULL;
    i = 0;
    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == ','))
            i++;
        j = i;
        while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != ','))
            i++;
        if (i > j)
        {
            split[k] = (char *)malloc(sizeof(char) * (i - j) + 1);
            ft_strncpy(split[k++], &str[j], i - j);
        }
    }
    split[k] = NULL;
    return(split);
}