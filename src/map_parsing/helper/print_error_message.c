/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:41:29 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/09 14:08:11 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err_msg(char *message1, char *message2, char *message3)
{
	char	*error_message;
	char	*temp;

	error_message = ft_strjoin("Error: ", message1);
	temp = error_message;
	error_message = ft_strjoin(error_message, message2);
	free(temp);
	temp = error_message;
	error_message = ft_strjoin(error_message, message3);
	ft_putendl_fd(error_message, STDERR_FILENO);
	free(temp);
	temp = NULL;
	free(error_message);
	error_message = NULL;
	return ;
}
