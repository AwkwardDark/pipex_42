/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:31:58 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/18 16:55:59 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		fd[2];
	char	*path;
	char	**cmd;
}	t_pipex;

//String Utils
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(int number, int size);
char	**ft_split(char const *s, char c);
void	ft_free(char **tab);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char  *s1, char  *s2);
void	ft_free(char **tab);

//Pipex Utils
void	ft_exec_cmd(char *cmd, char **envp);
int		ft_error(void);

#endif