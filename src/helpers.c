/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:29:54 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/18 11:50:10 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_filefds(t_filefds **file_fds)
{
	if (!*file_fds)
		return (1);
	(*file_fds)->fd_in = -1;
	(*file_fds)->fd_out = -1;
	return (0);
}

int	init_cp_struct(t_commandpaths **cp_struct)
{
	if (!*cp_struct)
		return (1);
	(*cp_struct)->cmd1_path = NULL;
	(*cp_struct)->cmd2_path = NULL;
	(*cp_struct)->cmd1 = NULL;
	(*cp_struct)->cmd2 = NULL;
	(*cp_struct)->fd_in = 0;
	(*cp_struct)->fd_out = 0;
	return (0);
}

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
	if (!cp_struct)
		return (1);
	free(cp_struct->cmd1_path);
	free(cp_struct->cmd2_path);
	free_all(cp_struct->cmd1);
	free_all(cp_struct->cmd2);
	free(cp_struct);
	return (0);
}

t_filefds	*open_create_files(char **argv)
{
	t_filefds	*file_fds;

	if (!argv)
		return (NULL);
	file_fds = malloc(sizeof(t_filefds));
	if (!file_fds)
		return (NULL);
	init_filefds(&file_fds);
	file_fds->fd_in = open(argv[1], O_RDONLY);
	if (file_fds->fd_in < 0)
	{
		perror(argv[1]);
		free(file_fds);
		exit(EXIT_FAILURE);
	}
	file_fds->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fds->fd_out < 0)
	{
		perror(argv[4]);
		close(file_fds->fd_in);
		free(file_fds);
		exit(EXIT_FAILURE);
	}
	return (file_fds);
}
