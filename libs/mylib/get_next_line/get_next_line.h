/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:37:51 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/06 12:16:52 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_get_next_line
{
	char		*current_line;
	char		*remainder;
}	t_line;

t_line		get_next_line(int fd);
char		*ft_my_substr(char const *s, unsigned int start, size_t len);
char		*ft_my_strjoin(char *s1, char *s2);
char		*ft_my_strdup(const char *s1);

#endif
