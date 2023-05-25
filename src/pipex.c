/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/25 16:59:21 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->pid == 0)
	{
		dup2(pipex->fd[1], 1);
		close(pipex->fd[0]);
		dup2(pipex->infile, 0);
		pipex->cmd = ft_split(argv[2], ' ');
	}
	else
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (ft_printf("Wrong number of arguments.\n"));
	if (access(argv[1], F_OK | R_OK))
		return (ft_printf("Error: %s \n", strerror(errno)));
	start_pipex(&pipex, argv, argc, envp);
	pipe(pipex.fd);
	pipex.pid = fork();
	if (pipex.pid == -1)
		error_msg("Failed to fork.", pipex);
	if (pipex.pid == 0)
		process(&pipex, argv, envp);
	waitpid(pipex.pid, NULL, 0);
	process(&pipex, argv, envp);
	closeall(&pipex);
	free_pipex(&pipex);
}
