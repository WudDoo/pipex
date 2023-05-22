/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:05:28 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/22 17:18:58 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
