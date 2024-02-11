/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:38:15 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:40:02 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	string_length;
	size_t	i;

	string_length = ft_strlen(s);
	i = 0;
	while (i <= string_length)
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i++;
	}
	return (NULL);
}
