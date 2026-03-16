/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:17:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/16 22:49:46 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex file1 cmd1 cmd2 file2
int	main(int argc, char **argv, char **envp)
{
	int				pipefd[2];
	char			*full_path;
	t_commandpaths	*cp_struct;
	t_filefds		*file_fds;

	if (argc < 5)
	{
		print_error(1);
		ft_printf("4 arguments needed, only %d recieved.\n", argc - 1);
		return (EINVAL);
	}
	pipe(pipefd);
	full_path = get_path(envp);
	file_fds = open_create_files(argv);
	cp_struct = get_cp_struct(argv, full_path, file_fds);
	fork_process(cp_struct, envp, pipefd, 1);
	fork_process(cp_struct, envp, pipefd, 2);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	free_struct(cp_struct);
	return (0);
}
