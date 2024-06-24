/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:01:18 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/21 15:49:50 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_find_path(char *cmd, char **envp, t_pipex *p)
{
	char	**paths;
	char	*append;
	char	*cmd_path;
	int		i;

	i = 0;
	while (envp[i] && strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i++])
	{
		append = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(append, cmd);
		free(append);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
		{
			free(paths);
			p->path = cmd_path;
			return ;
		}
		free(cmd_path);
	}
	ft_free(paths);
	p->path = NULL;
}

void	ft_exec_cmd(char *cmd, char **envp, t_pipex *p)
{
	char	**cmd_list;

	cmd_list = ft_split(cmd, ' ');
	if (!cmd_list)
		ft_error(5);
	ft_find_path(cmd_list[0], envp, p);
	if ((!p->path) && (access(cmd_list[0], F_OK | X_OK) == 0))
		p->path = cmd_list[0];
	if (!p->path)
	{
		ft_free(cmd_list);
		ft_error(4);
	}
	if (execve(p->path, cmd_list, envp) == -1)
	{
		ft_free(cmd_list);
		free(p->path);
		ft_error(0);
	}
	ft_free(cmd_list);
	free(p->path);
}

void	ft_error(int error)
{
	if (error == 0)
		ft_putstr_fd(ERR_EXEC, 2);
	else if (error == 1)
		ft_putstr_fd(ERR_OPEN, 2);
	else if (error == 2)
		ft_putstr_fd(ERR_PIPE, 2);
	else if (error == 3)
		ft_putstr_fd(ERR_PID, 2);
	else if (error == 4)
		ft_putstr_fd(ERR_CMD, 2);
	else if (error == 5)
		ft_putstr_fd(ERR_SPLIT, 2);
	else if (error == 6)
	{
		ft_putstr_fd(ERR_ARG, 2);
		ft_putstr_fd(FORMAT, 1);
	}
	exit(EXIT_FAILURE);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
