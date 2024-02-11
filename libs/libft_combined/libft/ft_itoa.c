/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:29:17 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/01 16:33:41 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static void	fill_string(char *a, int *i, int *j, int positive_n)
{
	int	ten_power;
	int	k;

	k = *i;
	ten_power = 10;
	if (k == 0)
		ten_power = 1;
	while (k > 1)
	{
		ten_power *= 10;
		k--;
	}
	a[*j] = (char)(((positive_n / ten_power) % 10) + 48);
	(*i)--;
	(*j)++;
}

static char	*itoa_int_min(char *a)
{
	int	i;
	int	j;
	int	positive_n;
	int	digits_num;

	digits_num = count_digits(-2147483648);
	i = digits_num - 1;
	j = 1;
	positive_n = 2147483647;
	a = (char *)ft_calloc((digits_num + 1 + 1), sizeof(char));
	if (!a)
		return (NULL);
	a[0] = '-';
	while (i >= 0)
		fill_string(a, &i, &j, positive_n);
	a[10] = '8';
	return (a);
}

static	char	*check_int_sign(int n, int digits_num, int positive_n, char *a)
{
	int		i;
	int		j;

	i = digits_num - 1;
	j = 0;
	if (n < 0)
	{
		positive_n = -n;
		a = (char *)ft_calloc((digits_num + 1 + 1), sizeof(char));
		if (!a)
			return (NULL);
		j = 1;
		a[0] = '-';
		while (i >= 0)
			fill_string(a, &i, &j, positive_n);
	}
	else if (n >= 0)
	{
		a = (char *)ft_calloc((digits_num + 1), sizeof(char));
		if (!a)
			return (NULL);
		while (i >= 0)
			fill_string(a, &i, &j, positive_n);
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int		digits_num;
	char	*a;
	int		positive_n;

	digits_num = count_digits(n);
	positive_n = n;
	a = NULL;
	if (n == -2147483648)
		return (itoa_int_min(a));
	return (check_int_sign(n, digits_num, positive_n, a));
}
