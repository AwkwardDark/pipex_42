/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:39:27 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/24 13:28:00 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_child_process(char **argv, char **envp, t_pipex *p)
{
	p->infile = open(argv[1], O_RDONLY, 0777);
	if (p->infile == -1)
		ft_error(1);
	close(p->fd[0]);
	dup2(p->infile, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[1]);
	ft_exec_cmd(argv[2], envp, p);
}

static void	ft_parent_process(char **argv, char **envp, t_pipex *p)
{
	p->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (p->outfile == -1)
		ft_error(1);
	close(p->fd[1]);
	dup2(p->fd[0], STDIN_FILENO);
	dup2(p->outfile, STDOUT_FILENO);
	close(p->fd[0]);
	ft_exec_cmd(argv[3], envp, p);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc == 5)
	{
		if (pipe(p.fd) == -1)
			ft_error(2);
		p.pid = fork();
		if (p.pid == -1)
			ft_error(3);
		if (p.pid == 0)
			ft_child_process(argv, envp, &p);
		waitpid(p.pid, NULL, 0);
		ft_parent_process(argv, envp, &p);
	}
	else
		ft_error(6);
	return (0);
}
