/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:17:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/16 17:44:58 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex file1 cmd1 cmd2 file2
int	main(int argc, char **argv, char **envp)
{
	int				pipefd[2];
	int				fd_in;
	int				fd_out;
	char			*full_path;
	t_commandpaths	*cp_struct;

	if (argc < 5)
	{
		print_error(1);
		ft_printf("4 arguments needed, only %d recieved.\n", argc - 1);
		return (EINVAL);
	}
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	pipe(pipefd);
	full_path = get_path(envp);
	cp_struct = get_cp_struct(argv, full_path, fd_in, fd_out);
	fork_process(cp_struct, envp, pipefd, 1);
	fork_process(cp_struct, envp, pipefd, 2);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	free(cp_struct);
	return (0);
}
