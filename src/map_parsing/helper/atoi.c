/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:55:48 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/09 14:08:11 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	skip_wsp_and_check_digit(char const c, int *digit_counter, bool *is_wsp)
{
	if (ft_isdigit(c))
	{
		if (*is_wsp)
			return (false);
		else
		{
			(*digit_counter)++;
			return (true);
		}
	}
	else if (c == '\t' || c == ' ')
	{
		*is_wsp = true;
		return (true);
	}
	else
		return (false);
}

bool	is_digit_or_wsp(char const *str)
{
	bool	is_wsp;
	int		i;
	int		digit_counter;

	digit_counter = 0;
	i = 0;
	is_wsp = false;
	while (str[i])
	{
		if (!skip_wsp_and_check_digit(str[i], &digit_counter, &is_wsp))
			return (false);
		i++;
	}
	if (digit_counter > 3)
		return (false);
	return (true);
}

bool	atoint(const char *str, int *color)
{
	int	sign;

	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\r' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!is_digit_or_wsp(str))
		return (false);
	while (ft_isdigit(*str))
	{
		*color = *color * 10 + (*str - '0');
		str++;
	}
	if (sign == -1)
		*color *= -1;
	return (true);
}
