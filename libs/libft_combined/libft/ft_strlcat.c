/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:07:07 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:40:41 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	initial_dst_length;
	size_t	src_length;

	i = 0;
	initial_dst_length = ft_strlen(dst);
	if (initial_dst_length > dstsize)
		initial_dst_length = dstsize;
	src_length = ft_strlen(src);
	if (dstsize > 0 && initial_dst_length < dstsize)
	{
		while (i < dstsize - initial_dst_length - 1 && src[i])
		{
			dst[initial_dst_length + i] = src[i];
			i++;
		}
		dst[initial_dst_length + i] = '\0';
	}
	return (initial_dst_length + src_length);
}
