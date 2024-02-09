/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:45:12 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/01 16:32:16 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_flag(char flag, char *remainders, int i)
{
	if (flag == 'X')
		ft_putchar_fd(ft_toupper(remainders[i]), 1);
	else
		ft_putchar_fd(remainders[i], 1);
}

static int	calc_required_memory(unsigned int a)
{
	int	i;

	i = 0;
	while (a > 0)
	{
		a /= 16;
		i++;
	}
	return (i);
}

static char	*convert_hex_to_string(unsigned int a)
{
	unsigned int		remainder;
	char				*remainders;
	int					i;

	i = calc_required_memory(a);
	remainders = malloc((i + 1) * sizeof(char));
	if (!remainders)
		return (NULL);
	remainder = a;
	i = 0;
	while (a > 0)
	{
		remainder = a % 16;
		if (remainder > 9)
			remainders[i] = (char)('a' - 10 + remainder);
		else
			remainders[i] = (char )(remainder + '0');
		a = a / 16;
		i++;
	}
	remainders[i] = '\0';
	return (remainders);
}

static int	print_result(va_list args, char flag)
{
	char				*remainders;
	unsigned int		a;
	int					i;
	int					count;

	count = 0;
	a = va_arg(args, unsigned int);
	if (a == 0)
	{
		ft_putchar_fd('0', 1);
		count++;
		return (count);
	}
	remainders = convert_hex_to_string(a);
	i = ft_strlen(remainders) - 1;
	while (i >= 0)
	{
		check_flag(flag, remainders, i);
		count++;
		i--;
	}
	free(remainders);
	return (count);
}

int	print_x(char format_specifier, int *i, va_list args)
{
	int		count;
	char	flag;

	flag = 'x';
	if (format_specifier == 'X')
		flag = 'X';
	count = print_result(args, flag);
	*i += 2;
	return (count);
}
