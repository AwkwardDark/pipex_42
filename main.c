/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:39:27 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/18 16:57:58 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(char **argv, char **envp, t_pipex *p)
{
	int	infile;

	// close(fd[0]);
	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		ft_error();
	dup2(infile, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[0]);
	ft_exec_cmd(argv[2], envp);
}

void	ft_parent_process(char **argv, char **envp, t_pipex *p)
{
	int	outfile;

	// close(fd[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		ft_error();
	dup2(p->fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(p->fd[1]);
	ft_exec_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	//fd[0] -> read
	//fd[1] -> write

	if (argc == 5)
	{
		if (pipe(p.fd) == -1)
			return (ft_error());
		p.pid = fork();
		if (p.pid == -1)
			return (ft_error());
		if (p.pid == 0)
			ft_child_process(argv, envp, &p);
		waitpid(p.pid, NULL, 0);
		ft_parent_process(argv, envp, &p);
		return (0);
	}
	else
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		ft_putstr_fd("Format: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 1);
		return (0);
	}
}
