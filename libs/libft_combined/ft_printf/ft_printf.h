/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:01:18 by fahmadia          #+#    #+#             */
/*   Updated: 2023/05/31 11:57:53 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

int			count_num_of_digits(long int n);
char		find_format_spec(const char *str, char format_specifier, int *i);
long int	to_power(long int n, int p);
int			ft_printf(const char *str, ...);
int			print_c(int *i, va_list args);
int			print_i(char format_specifier, int *i, va_list args);
int			print_p(int *i, va_list args);
int			print_percent(int *i);
int			print_s(int *i, va_list args);
int			print_x(char format_specifier, int *i, va_list args);
void		putnbr_long_int(long int n, int fd);
int			print_without_format_spec(const char *str, int *i);

#endif
