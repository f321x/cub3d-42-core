/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:11:11 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:37:03 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*p;
	char	*q;
	size_t	i;

	p = (char *)s1;
	q = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] == q[i])
		{
			i++;
			continue ;
		}
		return ((int)((unsigned char)p[i] - (unsigned char)q[i]));
	}
	return (0);
}
