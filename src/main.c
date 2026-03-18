/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:17:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/18 11:58:38 by ryatan           ###   ########.fr       */
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
	pid_t			pid1;
	pid_t			pid2;
	int				status1;
	int				status2;

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
	pid1 = fork_process_cmd1(cp_struct, envp, pipefd);
	pid2 = fork_process_cmd2(cp_struct, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	free_struct(cp_struct);
	if (WIFEXITED(status2) && WEXITSTATUS(status2) != 0)
		return (WEXITSTATUS(status2));
	if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
    	return (WEXITSTATUS(status1));
	return (0);
}
