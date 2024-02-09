/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_num_of_digits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:42:26 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/21 12:11:32 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_num_of_digits(long int n)
{
	long int		quotient;
	long int		digits_num;

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
