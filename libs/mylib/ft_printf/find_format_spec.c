/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_format_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:17:59 by fahmadia          #+#    #+#             */
/*   Updated: 2023/04/22 10:18:03 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	find_format_spec(const char *str, char format_specifier, int *i)
{
	if (str[*i + 1])
		format_specifier = str[*i + 1];
	return (format_specifier);
}
