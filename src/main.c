/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:17:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/15 15:59:51 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		if (argc == 1)
			print_error(0);
		else
			print_error(1);
		ft_printf("4 arguments needed, only %d recieved.\n", argc - 1);
		return (EINVAL);
	} 
	ft_printf("file 1: %s, cmd 1: %s, cmd 2: %s, file 2: %s\n",
			argv[1], argv[2], argv[3], argv[4]);
	return (0);
}
