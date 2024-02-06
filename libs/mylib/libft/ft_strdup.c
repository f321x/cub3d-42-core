/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:46:51 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:40:11 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_length;
	size_t	total_size;
	void	*p_new_string;

	s1_length = ft_strlen(s1);
	total_size = (s1_length + 1) * sizeof(char);
	p_new_string = malloc(total_size);
	if (!p_new_string)
		return (NULL);
	ft_strlcpy(p_new_string, s1, total_size);
	return (p_new_string);
}
