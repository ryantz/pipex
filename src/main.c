/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:17:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/07 09:47:04 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_commandpaths *cp_struct, char **envp, int *pipefd);

int	main(int argc, char **argv, char **envp)
{
	int				pipefd[2];
	t_commandpaths	*cp_struct;
	t_filefds		*file_fds;

	if (argc < 5)
	{
		print_error(1);
		ft_printf("4 arguments needed, only %d recieved.\n", argc - 1);
		return (EINVAL);
	}
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (1);
	}
	file_fds = open_create_files(argv);
	cp_struct = get_cp_struct(argv, get_path(envp), file_fds);
	if (!cp_struct)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	pipex(cp_struct, envp, pipefd);
	return (0);
}

void	pipex(t_commandpaths *cp_struct, char **envp, int *pipefd)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	pid1 = fork_process_cmd1(cp_struct, envp, pipefd);
	pid2 = fork_process_cmd2(cp_struct, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	close(cp_struct->fd_in);
	close(cp_struct->fd_out);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	free_struct(cp_struct);
	if (WIFEXITED(status2) && WEXITSTATUS(status2) != 0)
		exit(WEXITSTATUS(status2));
	if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
		exit(WEXITSTATUS(status1));
}
