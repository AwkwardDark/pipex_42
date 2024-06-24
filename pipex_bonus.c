/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:39:27 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/24 13:31:33 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_open_file(char **argv, int argc, int flag, t_pipex *p)
{
	if (flag == 0)
	{
		p->infile = open(argv[1], O_RDONLY, 0777);
		if (p->infile == -1)
			ft_error(1);
	}
	else if (flag == 1)
	{
		p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (p->outfile == -1)
			ft_error(1);
	}
	else if (flag == 2)
	{
		p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (p->outfile == -1)
			ft_error(1);
	}
}

static void	ft_child_process(char *argv, char **envp, t_pipex *p)
{
	if (pipe(p->fd) == -1)
		ft_error(2);
	p->pid = fork();
	if (p->pid == -1)
		ft_error(3);
	if (p->pid == 0)
	{
		close(p->fd[0]);
		dup2(p->fd[1], STDOUT_FILENO);
		close(p->fd[1]);
		ft_exec_cmd(argv, envp, p);
	}
	else
	{
		close(p->fd[1]);
		dup2(p->fd[0], STDIN_FILENO);
		close(p->fd[0]);
		waitpid(p->pid, NULL, 0);
	}
}

static void	ft_free_exit(t_pipex *p)
{
	free(p->line);
	get_next_line(0, 1);
	exit(EXIT_SUCCESS);
}

static void	ft_heredoc(char *limiter, t_pipex *p)
{
	if (pipe(p->fd) == -1)
		ft_error(2);
	p->pid = fork();
	if (p->pid == -1)
		ft_error(3);
	if (p->pid == 0)
	{
		close(p->fd[0]);
		while (1)
		{
			p->line = get_next_line(0, 0);
			if (strncmp(p->line, limiter, ft_strlen(p->line) - 1) == 0)
				ft_free_exit(p);
			ft_putstr_fd(p->line, p->fd[1]);
			free(p->line);
		}
	}
	else
	{
		close(p->fd[1]);
		dup2(p->fd[0], STDIN_FILENO);
		waitpid(p->pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		i;

	if (argc < 5)
		ft_error(6);
	if (strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			ft_error(7);
		i = 3;
		ft_open_file(argv, argc, 2, &p);
		ft_heredoc(argv[2], &p);
	}
	else
	{
		i = 2;
		ft_open_file(argv, argc, 0, &p);
		ft_open_file(argv, argc, 1, &p);
		dup2(p.infile, STDIN_FILENO);
	}
	while (i < argc - 2)
		ft_child_process(argv[i++], envp, &p);
	dup2(p.outfile, STDOUT_FILENO);
	ft_exec_cmd(argv[argc - 2], envp, &p);
	return (0);
}
