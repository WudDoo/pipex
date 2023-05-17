/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/17 15:58:53 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_paths(char **envp)
{
	char	*path;
	int		line;
	int		character;

	line = 0;
	path = "PATH=";
	while (envp[line])
	{
		character = 0;
		if (envp[line][character] == path[character])
		{
			while (envp[line][character] == path[character] && path[character])
				character++;
			if (!path[character])
				break ;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		infile;
	int		outfile;

	if (argc != 5)
		return (write(1, "Wrong number of arguments.\n", 27));
	if (access(argv[1], F_OK | R_OK))
		return (printf("%s \n", strerror(errno)));
	pipex.path_in = argv[1];
	pipex.path_out = argv[4];
	infile = open(pipex.path_in, O_RDONLY);
	outfile = open(pipex.path_out, O_RDWR | O_CREAT | O_TRUNC, 00777);
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	dup2(infile, 0);
	dup2(outfile, 1);
	printf("%s\n", envp[1]);
	close(infile);
	close(outfile);
}
