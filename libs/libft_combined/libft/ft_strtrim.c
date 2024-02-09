/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:47:54 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:42:27 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		j;
	char	*s1_trimmed;
	size_t	size_to_copy;

	start = 0;
	end = 0;
	j = (int)ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[start] && j > 0 && ft_strchr(set, s1[j]))
	{
		end++;
		j--;
	}
	size_to_copy = ft_strlen(s1) - start - end;
	s1_trimmed = malloc((size_to_copy + 1) * sizeof(char));
	if (!s1_trimmed)
		return (NULL);
	ft_memcpy(s1_trimmed, s1 + start, size_to_copy);
	s1_trimmed[size_to_copy] = '\0';
	return (s1_trimmed);
}
