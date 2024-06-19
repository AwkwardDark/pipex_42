/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:39:27 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/19 17:02:57 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(char *argv, char **envp, t_pipex *p)
{
	if (pipe(p->fd) == -1)
		ft_error();
	p->pid = fork();
	if (p->pid == -1)
			ft_error();
	if (p->pid == 0)
	{
		close(p->fd[0]);
		dup2(p->fd[1], STDOUT_FILENO);
		ft_exec_cmd(argv, envp);
	}
	else
	{
		close(p->fd[1]);
		dup2(p->fd[0], STDIN_FILENO);
		waitpid(p->pid, NULL, 0);
	}
}

void	ft_parent_process(char **argv, char **envp, t_pipex *p)
{
	dup2(p->fd[0], STDIN_FILENO);
	close(p->fd[1]);
	ft_exec_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		i;
	int		infile;
	int		outfile;

	if (argc >= 5)
	{
		if (strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND), 0777);
			ft_heredoc(argv[2], envp);
		}
		else
		{
			i = 2;
			infile = open(argv[1], O_RDONLY, 0777);
			if (infile == -1)
				ft_error();
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (outfile == -1)
				ft_error();
			dup2(infile, STDIN_FILENO);
		}
		while (i < argc- 2)
			ft_child_process(argv[i++], envp, &p);
		dup2(outfile, STDOUT_FILENO);
		ft_exec_cmd(argv[argc - 2], envp);
		return (0);
	}
	else
	{
		ft_putstr_fd("Wrong number of arguments\n\n", 2);
		ft_putstr_fd("Format: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 1);
		return (0);
	}
}
