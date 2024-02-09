/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:57:02 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/01 16:32:02 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_s(int *i, va_list args)
{
	char	*s;
	size_t	s_length;

	s = va_arg(args, char *);
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		*i += 2;
		return (6);
	}
	s_length = ft_strlen(s);
	ft_putstr_fd(s, 1);
	*i += 2;
	return (s_length);
}
