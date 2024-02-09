/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:39:14 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2023/04/14 12:22:26 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*p;

	total_size = count * size;
	if (count != 0 && total_size / count != size)
		return (NULL);
	p = malloc(total_size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, total_size);
	return (p);
}
