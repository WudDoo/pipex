/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/22 18:22:26 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process(t_pipex *pipex, char **argv, char **envp, int n)
{
	if (n == 1)
	{
		dup2(pipex->fd[1], 1);
		close(pipex->fd[0]);
		dup2(pipex->infile, 0);
		pipex->cmd = ft_split(argv[2], ' ');
	}
	else if (n == 2)
	{
		dup2(pipex->fd[0], 0);
		close(pipex->fd[1]);
		dup2(pipex->outfile, 1);
		pipex->cmd = ft_split(argv[3], ' ');
	}
	if (!pipex->cmd[0])
		pipex->cmd = ft_split("cat", ' ');
	pipex->cmd_path = get_cmd_path(*pipex, pipex->cmd[0]);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	execve(pipex->cmd_path, pipex->cmd, envp);
}

void	closeall(t_pipex *pipex)
{
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (ft_printf("Not enough arguments.\n"));
	if (access(argv[1], F_OK | R_OK))
		return (ft_printf("Error: %s \n", strerror(errno)));
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 00777);
	pipex.directories = get_directories(envp);
	pipe(pipex.fd);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		process(&pipex, argv, envp, 1);
	waitpid(pipex.pid1, NULL, 0);
	process(&pipex, argv, envp, 2);
	closeall(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	free_pipex(&pipex);
}
