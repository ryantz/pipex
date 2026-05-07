/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:29:03 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/07 09:36:01 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int err_code)
{
	if (err_code == ERR_NO_FILE)
		write(2, "There is no such file / folder!\n", 32);
	else if (err_code == ERR_INVALID_INPUT)
		write(2, "Inputs are in the wrong format!\n", 32);
}
