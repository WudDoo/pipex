/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:30:05 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/19 20:22:42 by mortins-         ###   ########.fr       */
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
	pid_t		pid1;
	pid_t		pid2;
	int			fd[2];
	int			infile;
	int			outfile;
	char		**directories;
	char		**cmd;
	char		*cmd_path;
}	t_pipex;

char	**get_directories(char **envp);

#endif