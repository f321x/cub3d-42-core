/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:49:56 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2023/04/21 12:25:09 by ***REMOVED***         ###   ########.fr       */
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