/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_long_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:46:02 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/21 12:30:27 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_long_int(long int n, int fd)
{
	long int	temp;
	int			power;
	long int	num;

	num = n;
	temp = num;
	power = count_num_of_digits(num);
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
			temp = num / (to_power(10, power - 1)) % 10 + 48;
			ft_putchar_fd(temp, fd);
			temp = num;
			power--;
		}
	}
}
