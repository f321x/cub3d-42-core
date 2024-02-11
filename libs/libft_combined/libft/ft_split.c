/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:01:10 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 12:35:53 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(int *flag, int j, char **strings)
{
	while (j >= 0)
	{
		free(strings[j]);
		j--;
	}
	free(strings);
	*flag = 1;
	return (NULL);
}

static int	strings_num(char const *s, char c)
{
	int		is_delimiter;
	int		num;

	is_delimiter = 0;
	num = 0;
	while (*s)
	{
		if (*s != c && is_delimiter == 0)
		{
			num++;
			is_delimiter = 1;
		}
		if (*s == c)
			is_delimiter = 0;
		s++;
	}
	return (num);
}

static char	**fill_string(char **strings, char const *s, char c, int *flag)
{
	int		length;
	int		i;
	int		j;

	length = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			return (strings);
		while (s[i + length] && s[i + length] != c)
			length++;
		strings[j] = (char *)ft_calloc((length + 1), sizeof(char));
		if (!strings[j])
			return (ft_free(flag, j, strings));
		ft_memcpy(strings[j], &s[i], length);
		i += length;
		length = 0;
		j++;
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		flag;

	flag = 0;
	if (!s)
		return (NULL);
	strings = (char **)ft_calloc((strings_num(s, c) + 1), sizeof(char *));
	if (!strings)
		return (NULL);
	fill_string(strings, s, c, &flag);
	if (flag == 1)
		return (NULL);
	return (strings);
}
