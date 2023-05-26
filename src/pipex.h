/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:30:05 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/26 17:56:08 by mortins-         ###   ########.fr       */
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

void	child(char **argv, char **envp, int *fd);
void	parent(char **argv, char **envp, int *fd);
void	execute(char *cmd_raw, char **envp);
int		command_exists(char *cmd_raw, char **envp);
char	**get_directories(char **envp);
char	*get_cmd_path(char **directories, char *cmd);
void	free_array(char	**array);

#endif