/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:54:08 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 17:20:34 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];
	int			buf_len;

	if (line == NULL || fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (ERROR);
	*line = NULL;
	if (update_line_with_buffer(line, buf[fd]) == ERROR)
		return (clear_and_quit(ERROR, line));
	while (ft_strlen(buf[fd]) == 0)
	{
		buf_len = read(fd, buf[fd], BUFFER_SIZE);
		if (buf_len <= 0)
			return (clear_and_quit(buf_len, line));
		if (update_line_with_buffer(line, buf[fd]) == ERROR)
			return (clear_and_quit(ERROR, line));
	}
	bufshift(buf[fd], SHIFT_NEWLINE);
	return (OK);
}

int	update_line_with_buffer(char **line, char *buf)
{
	*line = (char *)realloc_line(*line, buf);
	if (*line == NULL)
		return (ERROR);
	strcat_buf_in_line(*line, buf);
	bufshift(buf, NOT_SHIFT_NEWLINE);
	return (OK);
}

char	*realloc_line(char *line, char *buf)
{
	char	*new_line;
	int		len;
	int		i;

	len = get_line_len(line, buf);
	new_line = (char *)malloc((len + 1) * sizeof(char));
	if (new_line == NULL)
	{
		if (line)
			free(line);
		return (NULL);
	}
	i = 0;
	while (line && line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < (len + 1))
		new_line[i++] = '\0';
	if (line)
		free(line);
	return (new_line);
}

void	strcat_buf_in_line(char *line, char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (line[i])
		i++;
	j = 0;
	while (buf[j] && buf[j] != '\n')
	{
		line[i + j] = buf[j];
		j++;
	}
	line[i + j] = '\0';
}

void	bufshift(char buf[BUFFER_SIZE + 1], int should_shift_newline)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
	{
		i++;
	}
	if (should_shift_newline)
	{
		i++;
	}
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	while (buf[j])
	{
		buf[j] = '\0';
		j++;
	}
}
