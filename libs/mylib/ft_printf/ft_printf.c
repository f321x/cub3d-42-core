/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:04:14 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/22 12:45:06 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check(char format_specifier, int *count, int *i, va_list args)
{
	int	counter;

	counter = *count;
	if (format_specifier == 'c')
		counter += print_c(i, args);
	if (format_specifier == 'i' || format_specifier == 'd'
		|| format_specifier == 'u')
		counter += print_i(format_specifier, i, args);
	if (format_specifier == 's')
		counter += print_s(i, args);
	if (format_specifier == 'x' || format_specifier == 'X')
		counter += print_x(format_specifier, i, args);
	if (format_specifier == 'p')
		counter += print_p(i, args);
	if (format_specifier == '%')
		counter += print_percent(i);
	*count = counter;
}

int	ft_printf(const char *str, ...)
{
	char	format_specifier;
	int		i;
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	i = 0;
	format_specifier = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			format_specifier = find_format_spec(str, format_specifier, &i);
			check(format_specifier, &count, &i, args);
			continue ;
		}
		count += print_without_format_spec(str, &i);
	}
	va_end(args);
	return (count);
}
