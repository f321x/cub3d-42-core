/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:01:37 by fbock             #+#    #+#             */
/*   Updated: 2023/10/09 14:28:21 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*return_struct;

	return_struct = malloc(sizeof(t_list));
	if (!return_struct)
		return (NULL);
	return_struct->content = content;
	return_struct->next = NULL;
	return (return_struct);
}
