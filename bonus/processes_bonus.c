/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:51:58 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/31 14:53:48 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	process(char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("Error");
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute(cmd, envp);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

void	execute(char *cmd_raw, char **envp)
{
	char	**directories;
	char	*cmd_path;
	char	**cmd;

	cmd = ft_split(cmd_raw, ' ');
	if (!cmd[0])
		cmd = ft_split("cat", ' ');
	directories = get_directories(envp);
	cmd_path = get_cmd_path(directories, cmd[0]);
	free_array(directories);
	if (!cmd_path)
	{
		free_array(cmd);
		free(cmd_path);
		exit (1);
	}
	if (execve(cmd_path, cmd, envp) == -1)
	{
		free_array(cmd);
		free(cmd_path);
		exit (1);
	}
}
