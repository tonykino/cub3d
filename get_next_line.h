/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:56:08 by tokino            #+#    #+#             */
/*   Updated: 2020/12/18 14:56:10 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# define OK 1
# define ERROR -1

# define SHIFT_NEWLINE 1
# define NOT_SHIFT_NEWLINE 0

void	bufshift(char buf[BUFFER_SIZE + 1], int should_shift_newline);
int		clear_and_quit(int res, char **line);
int		get_line_len(char *line, char *buf);
int		get_next_line(int fd, char **line);
char	*realloc_line(char *line, char *buf);
void	strcat_buf_in_line(char *line, char *buf);
int		update_line_with_buffer(char **line, char *buf);

#endif
