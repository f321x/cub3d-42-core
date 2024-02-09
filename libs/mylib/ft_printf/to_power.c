/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:49:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/21 12:25:09 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	to_power(long int n, int p)
{
	long int	power;

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
