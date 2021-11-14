/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 15:09:14 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 17:20:01 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	clear_and_quit(int res, char **line)
{
	if (res == ERROR && *line)
	{
		free(*line);
		*line = NULL;
	}
	return (res);
}

int	get_line_len(char *line, char *buf)
{
	int	len;

	len = 0;
	while (buf[len] && buf[len] != '\n')
		len++;
	if (line)
		len += ft_strlen(line);
	return (len);
}
