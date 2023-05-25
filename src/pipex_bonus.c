/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:14:06 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/25 17:46:58 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	funcao(t_pipex *pipex, char **argv, char **envp, int cmd_n)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		error_msg("Failed to fork.", *pipex);
	if (pid == 0 && cmd_n == 2)
	{
		first_child(pipex, fd);
		execute(pipex, argv, envp, cmd_n);
	}
	else if (pid == 0)
	{
		child(fd);
		execute(pipex, argv, envp, cmd_n);
	}
	else
	{
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		cmd_max;
	int		cmd_n;

	if (argc < 5)
		return (ft_printf("Error: Not enough arguments.\n"));
	if (access(argv[1], F_OK | R_OK))
		return (ft_printf("Error: %s \n", strerror(errno)));
	cmd_max = argc - 3;
	cmd_n = 2;
	start_pipex(&pipex, argv, argc, envp);
	while (cmd_n != cmd_max)
	{
		funcao(&pipex, argv, envp, cmd_n++);
		ft_putstr_fd("while\n", pipex.outfile);
	}
	parent(&pipex, pipex.fd);
	execute(&pipex, argv, envp, cmd_n);
	close(pipex.fd[1]);
	close(pipex.fd[0]);
	free_pipex(&pipex);
}
