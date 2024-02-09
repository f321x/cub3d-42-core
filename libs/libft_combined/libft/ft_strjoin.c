/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:55:27 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:40:32 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	size_t	total_size;
	char	*p_new_string;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	total_size = s1_length + s2_length + 1;
	p_new_string = malloc(total_size * sizeof(char));
	if (!p_new_string || (!s1 && !s2))
		return (NULL);
	ft_memcpy(p_new_string, s1, s1_length + 1);
	ft_strlcat(p_new_string, s2, total_size);
	return (p_new_string);
}
