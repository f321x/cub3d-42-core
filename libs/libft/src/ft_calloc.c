/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:55:55 by fbock             #+#    #+#             */
/*   Updated: 2023/10/06 10:33:19 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*array;
	size_t	amount;
	size_t	index;

	amount = num * size;
	index = 0;
	array = malloc(amount);
	if (array == NULL)
		return (NULL);
	while (amount-- > 0)
		((unsigned char *)array)[index++] = 0;
	return (array);
}
