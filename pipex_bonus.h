/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:31:58 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/24 13:27:50 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

# define FORMAT_H "Format: ./pipex here_doc <limiter> <cmd1> <cmd2> <outfile>\n"
# define FORMAT   "Format: ./pipex <infile> <cmd1> <...> <cmdn> <outfile>\n"
# define ERR_ARG  "Wrong number of arguments\n"
# define ERR_EXEC "An error ocurred while executind the command\n"
# define ERR_OPEN "An error ocurred while opening the file\n"
# define ERR_PIPE "Problem creating the pipe\n"
# define ERR_PID  "Problem with the fork() function\n"
# define ERR_CMD "Command not found in any path\n"
# define ERR_SPLIT "AN error ocurrend with ft_split\n"

typedef struct s_pipex
{
	pid_t	pid;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*path;
	char	*line;
}	t_pipex;

//Pipex Utils
void	ft_exec_cmd(char *cmd, char **envp, t_pipex *p);
void	ft_error(int error);
void	ft_free(char **tab);

//String Utils
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(int number, int size);
char	**ft_split(char const *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_strchr(char *str, char c);

//gnl main functions
char	*get_next_line(int fd, int flag);
char	*ft_read_line(char *buffer, int fd);
char	*ft_join_free(char *buffer, char *temp_buffer);
char	*ft_write_line(char *buffer);
char	*ft_clean_buffer(char *buffer);

#endif