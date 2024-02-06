/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:08:10 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/01 16:31:55 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_required_memory(size_t a)
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

static char	*convert_address_to_string(size_t address)
{
	size_t				remainder;
	char				*remainders;
	int					i;

	i = calc_required_memory(address);
	remainders = malloc((i + 1) * sizeof(char));
	if (!remainders)
	{
		free(remainders);
		return (NULL);
	}
	i = 0;
	remainder = address ;
	while (address > 0)
	{
		remainder = address % 16;
		if (remainder > 9)
			remainders[i] = (char)('a' - 10 + remainder);
		else
			remainders[i] = (char )(remainder + '0');
		address = address / 16;
		i++;
	}
	remainders[i] = '\0';
	return (remainders);
}

static int	print_result(void *p)
{
	size_t	address;
	int		count;
	char	*remainders;
	int		i;

	address = (size_t)p;
	count = 0;
	i = 0;
	if (address == 0)
	{
		ft_putchar_fd('0', 1);
		count++;
	}
	remainders = convert_address_to_string(address);
	i = ft_strlen(remainders) - 1;
	while (i >= 0)
	{
		ft_putchar_fd(remainders[i], 1);
		count++;
		i--;
	}
	free(remainders);
	return (count);
}

int	print_p(int *i, va_list args)
{
	int		count;
	void	*p;

	count = 0;
	p = va_arg(args, void *);
	ft_putstr_fd("0x", 1);
	count = print_result(p);
	count += 2;
	*i += 2;
	return (count);
}
