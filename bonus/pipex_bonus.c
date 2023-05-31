/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:37:11 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/31 14:24:41 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	cmd_n;

	if (argc < 5)
		return (ft_printf("Error: Wrong number of arguments.\n"));
	if (access(argv[1], F_OK | R_OK) == -1)
		return (ft_printf("Error: %s\n", strerror(errno)));
	pipe_parser(argc, argv);
	infile = open(argv[1], O_RDONLY);
	dup2(infile, 0);
	close(infile);
	cmd_n = 2;
	while (cmd_n != argc - 2)
		process(argv[cmd_n++], envp);
	outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00777);
	dup2(outfile, 1);
	close(outfile);
	execute(argv[cmd_n], envp);
	return (0);
}
