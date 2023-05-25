/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:30:05 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/25 16:27:45 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/src/libft.h"
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t		pid;
	int			fd[2];
	int			infile;
	int			outfile;
	char		**directories;
	char		**cmd;
	char		*cmd_path;
}	t_pipex;

void	start_pipex(t_pipex *pipex, char **argv, int argc, char **envp);
char	**get_directories(char **envp);
char	*get_cmd_path(t_pipex pipex, char *cmd);
void	error_msg(char	*msg, t_pipex pipex);
void	closeall(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
void	free_child(t_pipex *pipex);

#endif