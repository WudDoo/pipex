/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:05:28 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/25 16:59:08 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_pipex(t_pipex *pipex, char **argv, int argc, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00777);
	pipex->directories = get_directories(envp);
}

char	**get_directories(char **envp)
{
	while (strncmp(*envp, "PATH", 4) != 0)
		envp++;
	return (ft_split(*envp + 5, ':'));
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
