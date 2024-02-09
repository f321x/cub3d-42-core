/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_without_format_spec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:18:26 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2023/04/22 10:18:29 by ***REMOVED***         ###   ########.fr       */
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
