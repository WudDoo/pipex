/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:18:38 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/25 16:32:33 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char	*msg, t_pipex pipex)
{
	ft_printf("Error: %s\n", msg);
	closeall(&pipex);
	free_pipex(&pipex);
	exit (0);
}

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
	if (pipex->cmd)
		free(pipex->cmd);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
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
