/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:23:57 by fbock             #+#    #+#             */
/*   Updated: 2023/10/10 10:39:26 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_memset(void *b, int c, size_t num)
{
	void	*b_start;
	char	*pointer;

	b_start = b;
	pointer = (char *)b;
	while (num > 0)
	{
		*pointer = c;
		pointer++;
		num--;
	}
	return (b_start);
}

/* int main()
{
	char		test[] = "dlsfsdkfnksdjnfdjksnf";
	size_t		size = 22;

	ft_memset((void *)test, 'e', size);
	printf("%s", test);
	return (1);
} */
