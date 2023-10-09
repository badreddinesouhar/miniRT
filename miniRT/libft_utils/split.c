/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:12:52 by aet-tass          #+#    #+#             */
/*   Updated: 2023/10/07 03:07:33 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

unsigned int	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	if (start <= ft_strlen(s))
	{
		while (i < len)
		{
			new_str[i] = s[start];
			i++;
			start++;
		}
		new_str[i] = '\0';
	}
	else
		new_str[0] = '\0';
	return (new_str);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		len_s;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dest)
		return (NULL);
	while (j < count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		len_s = 0;
		while (s[i] && s[i] != c)
		{
			len_s++;
			i++;
		}
		dest[j] = ft_substr(s, (i - len_s), len_s);
		j++;
	}
	dest[j] = NULL;
	return (dest);
}
