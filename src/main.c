/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:17:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/03/16 10:26:04 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	// read and write fds thats why it is 2
	int	pipefds[2];
	char	*buffer;
	char	*file1 = argv[1];
	char	*file2 = argv[4];
	char	*cmd1 = argv[2];
	char	*cmd2 = argv[3];

	printf("parent pid: %d\n", getpid());
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
			file1, cmd1, cmd2, file2);
	pipe(pipefds);
	write(pipefds[1], file1, ft_strlen(argv[1]));
	// child runs from this line
	if (fork() > 0)
		return (1);
	buffer = malloc(sizeof(char) * (ft_strlen(argv[1])));
	read(pipefds[0], buffer, ft_strlen(argv[1]) + 1);
	printf("got from pipe: %s\n", buffer);
	printf("child pid: %d\n", getpid());
	free(buffer);
	return (0);
}
