/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:37:59 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/26 18:14:32 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/src/libft.h"
# include <sys/wait.h>

void	process(char *cmd, char **envp);
void	execute(char *cmd_raw, char **envp);
int		command_exists(char *cmd_raw, char **envp);
char	**get_directories(char **envp);
char	*get_cmd_path(char **directories, char *cmd);
void	free_array(char	**array);

#endif