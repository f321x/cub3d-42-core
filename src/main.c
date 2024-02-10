/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by fbock             #+#    #+#             */
/*   Updated: 2024/02/07 10:14:08 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv)
{
	t_conf_file	config_file;

	if (!parse_config_file(argc, argv, &config_file))
		return (config_file.error);
	print_test(config_file);
	free_config_file_members(&config_file);
	return (0);
}
