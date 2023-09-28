/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 06:35:37 by bsouhar           #+#    #+#             */
/*   Updated: 2023/09/29 00:51:45 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

char	*ft_strncpy(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (i < len && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	**ft_split(char *str)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int wc = 0;

	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
				|| str[i] == ','))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
				&& str[i] != ','))
			i++;
	}
	char **split = (char **)malloc(sizeof(char *) * wc + 1);
	if (!split)
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
				|| str[i] == ','))
			i++;
		j = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
				&& str[i] != ','))
			i++;
		if (i > j)
		{
			split[k] = (char *)malloc(sizeof(char) * (i - j) + 1);
			ft_strncpy(split[k++], &str[j], i - j);
		}
	}
	split[k] = NULL;
	return (split);
}

char *ft_strtrim(char *str) {
    if (!str)
        return NULL;

    int i = 0;
    int j = 0;
    int len = 0;
    int trimming = 1; // Indicates whether we are in trimming mode (leading spaces)

    while (str[i]) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\v') {
            if (!trimming) {
                trimming = 1;
                str[j++] = ' ';
                len++;
            }
        } else {
            trimming = 0;
            str[j++] = str[i];
            len++;
        }
        i++;
    }

    // Handle trailing spaces
    while (j > 0 && (str[j - 1] == ' ' || str[j - 1] == '\t' || str[j - 1] == '\v')) {
        j--;
        len--;
    }

    str[j] = '\0';

    return str;
}
