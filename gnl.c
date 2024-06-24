/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:27:18 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/21 15:27:16 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_join_free(char *buffer, char *temp_buffer)
{
	char	*str;

	str = ft_strjoin(buffer, temp_buffer);
	free(buffer);
	buffer = str;
	return (buffer);
}

char	*ft_read_line(char *buffer, int fd)
{
	char	*temp_buffer;
	int		char_read;

	if (!buffer)
		buffer = ft_calloc(sizeof(char), 1);
	temp_buffer = ft_calloc(sizeof(char), 2);
	if (!temp_buffer)
		return (NULL);
	char_read = 1;
	while (char_read > 0)
	{
		char_read = read(fd, temp_buffer, 1);
		if (char_read == -1)
		{
			free(temp_buffer);
			free(buffer);
			return (NULL);
		}
		temp_buffer[char_read] = '\0';
		buffer = ft_join_free(buffer, temp_buffer);
		if (ft_strchr(temp_buffer, '\n'))
			break ;
	}
	free(temp_buffer);
	return (buffer);
}

char	*ft_write_line(char *buffer)
{
	int		len;
	char	*next_line;

	len = 0;
	if (!buffer[len])
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	next_line = ft_calloc(sizeof(char), len + 2);
	if (!next_line)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
	{
		next_line[len] = buffer[len];
		len++;
	}
	if (buffer[len] && buffer[len] == '\n')
		next_line[len++] = '\n';
	return (next_line);
}

char	*ft_clean_buffer(char *buffer)
{
	char	*new_buffer;
	int		len;
	int		i;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (!buffer[len])
	{
		free(buffer);
		return (NULL);
	}	
	new_buffer = ft_calloc(sizeof(char), ft_strlen(buffer) - len + 1);
	if (!new_buffer)
		return (NULL);
	i = 0;
	len++;
	while (buffer[len + i])
	{
		new_buffer[i] = buffer[len + i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd, int flag)
{
	static char	*buffer;
	char		*next_line;

	if (flag)
	{
		free(buffer);
		return (NULL);
	}
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_read_line(buffer, fd);
	if (!buffer)
		return (NULL);
	next_line = ft_write_line(buffer);
	buffer = ft_clean_buffer(buffer);
	return (next_line);
}
