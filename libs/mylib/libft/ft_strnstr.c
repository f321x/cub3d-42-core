/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:40:51 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:42:09 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;
	int		result_memcmp;

	i = 0;
	len_needle = ft_strlen(needle);
	if (!len_needle)
		return ((char *)(haystack));
	while (i < len)
	{
		if (!haystack[i])
			return (NULL);
		result_memcmp = ft_memcmp(haystack + i, needle, len_needle);
		if (result_memcmp == 0 && len_needle + i <= len)
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
