/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/26 17:57:21 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	if (argc != 5)
		return (ft_printf("Error: Wrong number of arguments.\n"));
	if (access(argv[1], F_OK | R_OK) == -1)
		return (ft_printf("Error: %s\n", strerror(errno)));
	i = 2;
	while (i != argc - 1)
		command_exists(argv[i++], envp);
	if (pipe(fd) == -1)
	{
		perror("Error");
		exit (0);
	}
	pid = fork();
	if (pid == 0)
		child(argv, envp, fd);
	waitpid(pid, NULL, 0);
	parent(argv, envp, fd);
}
