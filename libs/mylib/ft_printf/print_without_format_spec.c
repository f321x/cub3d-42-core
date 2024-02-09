/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_without_format_spec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:18:26 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/22 10:18:29 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_without_format_spec(const char *str, int *i)
{
	int	count;

	count = 0;
	if (str[*i] != '%')
	{
		ft_putchar_fd(str[*i], 1);
		(*i)++;
		count++;
	}
	return (count);
}
