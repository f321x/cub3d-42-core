/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 13:39:55 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/14 12:45:55 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_power(int n, int p)
{
	int	power;

	power = n;
	if (p == 0)
		return (1);
	while (p > 1)
	{
		power *= n;
		p--;
	}
	return (power);
}

static int	count_digits(int n)
{
	int		quotient;
	int		digits_num;

	if (n == -2147483648)
		return (10);
	quotient = n;
	digits_num = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		quotient = -n;
	while (quotient > 0)
	{
		quotient /= 10;
		digits_num++;
	}
	return (digits_num);
}

void	ft_putnbr_fd(int n, int fd)
{
	int			temp;
	int			power;
	long int	num;

	num = n;
	temp = num;
	power = count_digits(num);
	if (num < 0)
	{
		num = -num;
		temp = num;
		ft_putchar_fd('-', fd);
	}
	if (num >= 0 && num <= 9)
		ft_putchar_fd(num + '0', fd);
	else
	{
		while (power > 0)
		{
			temp = num / (ft_power(10, power - 1)) % 10 + 48;
			ft_putchar_fd(temp, fd);
			temp = num;
			power--;
		}
	}
}
