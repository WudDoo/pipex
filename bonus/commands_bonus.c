/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:01:28 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/31 14:54:25 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_parser(int argc, char **argv)
{
	int	i;

	i = 3;
	while (i != argc - 2)
	{
		if (!argv[i][0])
		{
			ft_printf("Error: parse error near  \"\".\n");
			exit (0);
		}
		i++;
	}
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
