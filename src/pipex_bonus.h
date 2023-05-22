/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:20:54 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/22 17:41:18 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUX_H

# include "pipex.h"

typedef struct s_bonus
{
	pid_t		pid;
	int			fd[2];
	int			infile;
	int			outfile;
	int			cmd_max;
	int			cmd_n;
	char		**directories;
	char		**cmd;
	char		*cmd_path;
}	t_bonus;

#endif