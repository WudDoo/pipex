/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:06:32 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/25 17:51:54 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent(t_pipex *pipex, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
}

void	first_child(t_pipex *pipex, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
}

void	child(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	execute(t_pipex *pipex, char **argv, char**envp, int cmd_n)
{
	pipex->cmd = ft_split(argv[cmd_n], ' ');
	pipex->cmd_path = get_cmd_path(*pipex, pipex->cmd[0]);
	ft_putstr_fd("child\n", pipex->outfile);
	execve(pipex->cmd_path, pipex->cmd, envp);
	exit (0);
}
