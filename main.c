/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:39:27 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/17 20:01:11 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	close(fd[0]);
	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		ft_error();
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

void	ft_parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	close(fd[1]);
	outfile = read(fd[0], O_RDONLY, 0777);
	if (outfile == -1)
		ft_error();
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argv;
	int		fd[2];
	//fd[0] -> read
	//fd[1] -> write
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (ft_error());
		pid = fork();
		if (pid == -1)
			return (ft_error());
		if (pid == 0)
			ft_child_process(argv, envp, fd);
		ft_parent_process(argv, envp, fd);
		return (0);
	}
	else
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		ft_putstr_fd("Format: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 1);
		return (0);
	}
}
