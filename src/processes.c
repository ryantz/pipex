/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:22:08 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/17 20:47:56 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// argv[1]: file1, argv[2]: cmd1, argv[3]: cmd2, argv[4]: file2
// stdin = 0, stdout = 1, stderr = 2

char	*get_path(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	print_error(0);
	return (NULL);
}

char	*get_command_path(char *full_path, char *command)
{
	char	**split_paths;
	char	*path_join_command;
	char	*tmp;
	int		i;

	if (!full_path || !command)
		return (NULL);
	split_paths = ft_split(full_path, ':');
	i = 0;
	while (split_paths[i])
	{
		tmp = ft_strjoin(split_paths[i], "/");
		path_join_command = ft_strjoin(tmp, command);
		free(tmp);
		if (access(path_join_command, X_OK) == 0)
		{
			free_all(split_paths);
			return (path_join_command);
		}
		free(path_join_command);
		i++;
	}
	print_error(0);
	free(split_paths);
	return (NULL);
}

t_commandpaths	*get_cp_struct(char **argv, char *full_path, t_filefds *fds)
{
	char			**cmd1;
	char			**cmd2;
	char			*command1_path;
	char			*command2_path;
	t_commandpaths	*cp_struct;

	if (!argv || !full_path || !fds)
		return (NULL);
	cp_struct = malloc(sizeof(t_commandpaths));
	if (!cp_struct)
		return (NULL);
	init_cp_struct(&cp_struct);
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	command1_path = get_command_path(full_path, cmd1[0]);
	command2_path = get_command_path(full_path, cmd2[0]);
	cp_struct->cmd1_path = command1_path;
	cp_struct->cmd2_path = command2_path;
	cp_struct->cmd1 = cmd1;
	cp_struct->cmd2 = cmd2;
	cp_struct->fd_in = fds->fd_in;
	cp_struct->fd_out = fds->fd_out;
	free(fds);
	return (cp_struct);
}

void	fork_process(t_commandpaths *cp_struct, char **envp, int *pipefd,
		int cmd)
{
	pid_t	pid;

	if (!cp_struct || !envp || !pipefd)
		return ;
	pid = fork();
	if (pid == 0 && cmd == 1)
	{
		dup2(cp_struct->fd_in, 0);
		dup2(pipefd[1], 1);
		close(cp_struct->fd_in);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(cp_struct->cmd1_path, cp_struct->cmd1, envp);
	}
	else if (pid == 0 && cmd == 2)
	{
		dup2(pipefd[0], 0);
		dup2(cp_struct->fd_out, 1);
		close(cp_struct->fd_out);
		close(pipefd[1]);
		close(pipefd[0]);
		execve(cp_struct->cmd2_path, cp_struct->cmd2, envp);
	}
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
