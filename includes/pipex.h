/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:53:14 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/16 22:49:17 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"

# include <unistd.h> 
# include <fcntl.h> 
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

enum e_error
{
	ERR_NONE,
	ERR_INVALID_INPUT,
};

typedef struct s_commandpaths
{
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1;
	char	**cmd2;
	int		fd_in;
	int		fd_out;
}	t_commandpaths;

typedef struct s_filefds
{
	int	fd_in;
	int	fd_out;
}	t_filefds;

void			print_error(int err_code);
char			*get_path(char **envp);
char			*get_command_path(char *full_path, char *command);
t_commandpaths	*get_cp_struct(char **argv, char *full_path, t_filefds *fds);
void			fork_process(t_commandpaths *cp_struct, char **envp,
					int *pipefd, int cmd);
t_filefds		*open_create_files(char **argv);
int				free_all(char **item);
int				free_struct(t_commandpaths *cp_struct);

#endif
