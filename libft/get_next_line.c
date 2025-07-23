/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:31:37 by lpaysant          #+#    #+#             */
/*   Updated: 2025/07/22 18:29:09 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_buffrest(char *buffer, char **buffrest, int *i)
{
	char	*temp;

	if (buffer[*i + 1] != '\0')
	{
		*buffrest = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!*buffrest)
			return (NULL);
		*buffrest[0] = '\0';
		temp = ft_strjoin_gnl(*buffrest, buffer + *i + 1);
		free(*buffrest);
		if (!temp)
			return (NULL);
		*buffrest = temp;
		(*i)++;
		while (buffer[*i])
			buffer[(*i)++] = '\0';
	}
	return (*buffrest);
}

char	*create_line(char *buffer, char *line)
{
	char	*temp;

	if (line == NULL)
	{
		line = malloc(1 * sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	temp = ft_strjoin_gnl(line, buffer);
	if (!temp)
		return (free(line), NULL);
	free(line);
	line = temp;
	return (line);
}

char	*new_line(char **buffrest, char *buffer, int i, char *line)
{
	*buffrest = get_buffrest(buffer, buffrest, &i);
	if (!buffrest)
		buffrest = NULL;
	line = create_line(buffer, line);
	if (!line)
		return (free(buffer), NULL);
	free(buffer);
	return (line);
}

char	*linecheck(char *buffer, char **buffrest, int fd, int i)
{
	char	*line;
	int		nbread;

	line = NULL;
	nbread = 0;
	while (1)
	{
		if (buffer[i] == '\0')
		{
			line = create_line(buffer, line);
			if (!line)
				return (free(buffer), NULL);
			nbread = read(fd, buffer, BUFFER_SIZE);
			if (nbread < 0)
				return (free(line), free(buffer), free(*buffrest), NULL);
			if (nbread == 0)
				return (free(buffer), free(*buffrest), line);
			buffer[nbread] = '\0';
			i = 0;
		}
		if (buffer[i] == '\n')
			return (new_line(buffrest, buffer, i, line));
		i++;
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*buffrest;
	int			i;
	char		*line;

	i = 0;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, &buffrest);
	if (!buffer)
	{
		free(buffrest);
		buffrest = NULL;
		return (NULL);
	}
	line = linecheck(buffer, &buffrest, fd, i);
	if (!line)
	{
		free(buffrest);
		buffrest = NULL;
	}
	return (line);
}
