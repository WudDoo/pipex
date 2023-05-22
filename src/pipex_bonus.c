/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:14:06 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/22 17:26:03 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_bonus *pipex, char **argv, char **envp)
{
	if (pipex->cmd_n == 1)
	{
		dup2(pipex->fd[1], 1);
		close(pipex->fd[0]);
		dup2(pipex->infile, 0);
	}
	else if (pipex->cmd_n == pipex->cmd_max)
	{
		dup2(pipex->fd[0], 0);
		close(pipex->fd[1]);
		dup2(pipex->outfile, 1);
	}
	else
	{
		dup2(pipex->fd[0], 0);
		dup2(pipex->fd[1], 1);
	}
	pipex->cmd = ft_split(argv[pipex->cmd_n + 1], ' ');
	pipex->cmd_path = get_cmd_path(*pipex, pipex->cmd[0]);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	execve(pipex->cmd_path, pipex->cmd, envp);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_bonus	pipex;

	if (argc < 5)
		return (ft_printf("Not enough arguments.\n"));
	if (access(argv[1], F_OK | R_OK))
		return (ft_printf("Error: %s \n", strerror(errno)));
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00777);
	pipex.directories = get_directories(envp);
	pipe(pipex.fd);
	pipex.cmd_max = argc - 3;
	pipex.cmd_n = 1;
	while (pipex.cmd_n <= pipex.cmd_max)
	{
		pipex.pid = fork();
		if (pipex.pid == 0)
			child_process(&pipex, argv, envp);
		pipex.cmd_n++;
	}
	close(pipex.fd[1]);
	close(pipex.fd[0]);
	free_pipex(&pipex);
}
