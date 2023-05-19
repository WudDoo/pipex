/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/19 20:44:47 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->directories[i])
		free(pipex->directories[i++]);
	free(pipex->directories);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd[i])
		free(pipex->cmd[i++]);
	free(pipex->cmd);
	free(pipex->cmd_path);
}

void	error_msg(char	*msg, t_pipex pipex)
{
	ft_printf("Error: %s\n", msg);
	free_pipex(&pipex);
	exit (0);
}

char	*get_cmd_path(t_pipex pipex, char *cmd)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while (pipex.directories[i])
	{
		tmp = ft_strjoin(pipex.directories[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, 0) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	free_child(&pipex);
	error_msg("Command not found.", pipex);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_printf("Not enough arguments.\n"));
	if (access(argv[1], F_OK | R_OK))
		return (ft_printf("Error: %s \n", strerror(errno)));
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 00777);
	pipex.directories = get_directories(envp);
	pipe(pipex.fd);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		pipex.cmd = ft_split(argv[2], ' ');
		pipex.cmd_path = get_cmd_path(pipex, pipex.cmd[0]);
		dup2(pipex.fd[1], 1);
		close(pipex.fd[0]);
		dup2(pipex.infile, 0);
		execve(pipex.cmd_path, pipex.cmd, envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		pipex.cmd = ft_split(argv[3], ' ');
		pipex.cmd_path = get_cmd_path(pipex, pipex.cmd[0]);
		dup2(pipex.fd[0], 0);
		close(pipex.fd[1]);
		dup2(pipex.outfile, 1);
		execve(pipex.cmd_path, pipex.cmd, envp);
	}
	close(pipex.fd[1]);
	close(pipex.fd[0]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_pipex(&pipex);
}
