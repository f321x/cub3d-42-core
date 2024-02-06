/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:59:55 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 11:36:23 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_root;
	t_list	*added_list;
	void	*modified_content;

	new_root = NULL;
	while (lst)
	{
		modified_content = f(lst -> content);
		added_list = ft_lstnew(modified_content);
		if (!added_list)
		{
			ft_lstclear(&new_root, del);
			free(modified_content);
			return (new_root);
		}
		ft_lstadd_back(&new_root, added_list);
		lst = lst -> next;
	}
	return (new_root);
}
