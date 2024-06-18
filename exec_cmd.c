/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:01:18 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/18 16:55:13 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*append;
	char	*cmd_path;
	int	i;

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
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(paths);
	return (NULL);
}

void	ft_exec_cmd(char *cmd, char **envp)
{
	char	**cmd_list;
	char	*path;

	cmd_list = ft_split(cmd, ' ');
	if (!cmd_list)
		ft_error();
	path = ft_find_path(cmd_list[0], envp);
	if (!path)
	{
		ft_free(cmd_list);
		ft_error();
	}
	if (execve(path, cmd_list, envp) == -1)
		ft_error();
	ft_free(cmd_list);
	free(path);
}

int	ft_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
