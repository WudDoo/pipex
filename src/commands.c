/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:46:51 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/26 17:57:38 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	command_exists(char *cmd_raw, char **envp)
{
	char	**directories;
	char	*cmd_path;
	char	**cmd;

	directories = get_directories(envp);
	cmd = ft_split(cmd_raw, ' ');
	if (!cmd[0])
		cmd = ft_split("cat", ' ');
	cmd_path = get_cmd_path(directories, cmd[0]);
	if (cmd_path == 0)
	{
		free_array(directories);
		free_array(cmd);
		exit (0);
	}
	free(cmd_path);
	free_array(cmd);
	free_array(directories);
	return (1);
}

char	**get_directories(char **envp)
{
	while (strncmp(*envp, "PATH", 4) != 0)
		envp++;
	return (ft_split(*envp + 5, ':'));
}

char	*get_cmd_path(char **directories, char *cmd)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while (directories[i])
	{
		tmp = ft_strjoin(directories[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, 0) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	ft_putstr_fd("Error: Command not found.\n", STDERR_FILENO);
	return (0);
}

void	free_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
