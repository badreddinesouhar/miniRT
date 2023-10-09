/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 08:42:28 by bsouhar           #+#    #+#             */
/*   Updated: 2023/10/07 08:43:49 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	*ft_memset(void *str, int c, size_t len)
{
	char	*cast_str;
	size_t	i;

	i = 0;
	cast_str = (char *)str;
	while (i < len)
	{
		cast_str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*cast_str;

	i = 0;
	cast_str = (char *)str;
	while (cast_str[i] && cast_str[i] != (char)c)
		i++;
	if (cast_str[i] == (char)c)
		return (&cast_str[i]);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cast_s1;
	char	*final_str;
	size_t	len_s1;

	if (!s1 || !set)
		return (NULL);
	cast_s1 = (char *)s1;
	while (*cast_s1 && ft_strchr(set, *cast_s1))
		cast_s1++;
	len_s1 = ft_strlen(cast_s1);
	while (len_s1 && ft_strchr(set, cast_s1[len_s1]))
		len_s1--;
	final_str = ft_substr(cast_s1, 0, len_s1 + 1);
	free((char *)s1);
	return (final_str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}
