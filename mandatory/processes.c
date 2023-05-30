/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:52 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/26 17:11:22 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		ft_printf("Error: %s \n", strerror(errno));
		exit (0);
	}
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	dup2(infile, 0);
	close(infile);
	execute(argv[2], envp);
}

void	parent(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 00777);
	if (outfile < 0)
	{
		ft_printf("Error: %s \n", strerror(errno));
		exit (0);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	dup2(outfile, 1);
	close(outfile);
	execute(argv[3], envp);
}

void	execute(char *cmd_raw, char **envp)
{
	char	**directories;
	char	*cmd_path;
	char	**cmd;

	directories = get_directories(envp);
	cmd = ft_split(cmd_raw, ' ');
	if (!cmd[0])
		cmd = ft_split("cat", ' ');
	cmd_path = get_cmd_path(directories, cmd[0]);
	free_array(directories);
	if (execve(cmd_path, cmd, envp) == -1)
	{
		free_array(cmd);
		free(cmd_path);
		exit (0);
	}
}
