/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:20:54 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/25 17:41:49 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

void	parent(t_pipex *pipex, int *fd);
void	child(int *fd);
void	first_child(t_pipex *pipex, int *fd);
void	execute(t_pipex *pipex, char **argv, char**envp, int cmd_n);

#endif