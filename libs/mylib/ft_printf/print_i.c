/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:35:25 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/01 16:31:37 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_i(char format_specifier, int *i, va_list args)
{
	int					a;
	int					count;
	unsigned long int	b;

	count = 0;
	b = 0;
	a = va_arg(args, int);
	if (format_specifier == 'u' && a < 0)
	{
		b = to_power(2, 32) + a;
		putnbr_long_int(b, 1);
		*i += 2;
		return (10);
	}
	ft_putnbr_fd(a, 1);
	*i += 2;
	count = count_num_of_digits((long)a);
	if (a < 0)
		count++;
	return (count);
}
