/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:52:30 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/01 16:32:58 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*p_dst;
	char	*p_src;
	size_t	i;

	p_dst = (char *)dst;
	p_src = (char *)src;
	i = 0;
	if (!dst && !src && len)
		return (NULL);
	while (i < len)
	{
		if (src < dst)
		{
			p_dst[len - 1 - i] = p_src[len - 1 - i];
			i++;
		}
		else
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	return (p_dst);
}
