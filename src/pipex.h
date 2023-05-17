/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:30:05 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/17 15:35:57 by mortins-         ###   ########.fr       */
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

typedef struct s_pipex
{
	char	*path_in;
	char	*path_out;
	char	*cmd1;
	char	*par1;
	char	*cmd2;
	char	*par2;
}	t_pipex;

char	**ft_split(char const *s, char c);

#endif