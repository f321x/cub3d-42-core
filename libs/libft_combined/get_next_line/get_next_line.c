/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:38:01 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/06 12:17:08 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_current_line(char **remainder, int *i)
{
	char	*line;
	char	*temp;
	int		j;

	j = 0;
	while ((*remainder)[j])
		j++;
	line = ft_my_substr((*remainder), 0, *i + 1);
	temp = *remainder;
	if (j - *i - 1 == 0)
		*remainder = NULL;
	else
		*remainder = ft_my_substr(*remainder, *i + 1, j - *i - 1);
	free(temp);
	return (line);
}

static char	*get_last_line(char **remainder)
{
	char	*temp;

	temp = ft_my_strdup(*remainder);
	free(*remainder);
	if (!temp)
		return (NULL);
	*remainder = NULL;
	return (temp);
}

static void	*support_read(char **remainder)
{
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}

static char	*check_end(char *buffer, int *num, int fd, char **remainder)
{
	int	i;

	while (1)
	{
		i = 0;
		*remainder = ft_my_strjoin(*remainder, buffer);
		if (!*remainder)
			return (NULL);
		while ((*remainder)[i])
		{
			if ((*remainder)[i] == '\n')
				return (get_current_line(remainder, &i));
			i++;
		}
		if (!*num)
			return (get_last_line(remainder));
		i = 0;
		while (buffer[i])
			buffer[i++] = '\0';
		*num = read(fd, buffer, BUFFER_SIZE);
		if (*num < 0 || BUFFER_SIZE <= 0 || fd < 0)
			support_read(remainder);
	}
	return (NULL);
}

t_line	get_next_line(int fd)
{
	char		*buffer;
	int			num;
	static char	*remainder;
	t_line		results;

	ft_memset(&results, 0, sizeof(results));
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (results);
	num = read(fd, buffer, BUFFER_SIZE);
	if ((num < 0 || BUFFER_SIZE <= 0 || fd < 0) || (!num && !remainder))
	{
		if (remainder)
		{
			free(remainder);
			remainder = NULL;
		}
		free (buffer);
		return (results);
	}
	results.current_line = check_end(buffer, &num, fd, &remainder);
	results.remainder = remainder;
	return (free(buffer), results);
}
