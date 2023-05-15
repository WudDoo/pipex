/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/15 18:38:42 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
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
	outfile = open(pipex.path_out, O_RDWR); //add flag to create file if nonexistant and to clear the file before using it
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	dup2(infile, 0);
	dup2(outfile, 1);
	printf("%s\n%s", pipex.cmd1, pipex.cmd2);
	close(infile);
	close(outfile);
}
