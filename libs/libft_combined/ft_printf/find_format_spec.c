/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_format_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:17:59 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2023/04/22 10:18:03 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	find_format_spec(const char *str, char format_specifier, int *i)
{
	if (str[*i + 1])
		format_specifier = str[*i + 1];
	return (format_specifier);
}
