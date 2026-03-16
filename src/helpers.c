/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:29:54 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/16 22:49:59 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_all(char **item)
{
	int	i;
	
	if (!item)
		return (1);
	i = 0;
	while (item[i])
	{
		free(item[i]);
		i++;
	}
	free(item);
	return (0);
}

int	free_struct(t_commandpaths *cp_struct)
{
	free(cp_struct->cmd1_path);
	free(cp_struct->cmd2_path);
	free_all(cp_struct->cmd1);
	free_all(cp_struct->cmd2);
	free(cp_struct);
	return (0);
}
