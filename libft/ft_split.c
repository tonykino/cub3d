/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:52:56 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 18:10:43 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_word_cnt(char const *s, char *charset)
{
	int	i;
	int	count;

	if (s == NULL || s[0] == '\0')
	{
		return (0);
	}
	count = 0;
	if (!is_in_charset(s[0], charset))
	{
		count++;
	}
	i = 1;
	while (s[i])
	{
		if (is_in_charset(s[i - 1], charset) && !is_in_charset(s[i], charset))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static void	*free_ary(char **ary)
{
	int	i;

	i = 0;
	while (ary[i])
	{
		free(ary[i]);
		i++;
	}
	free(ary);
	return (NULL);
}

static int	get_next_word(char **ary, char const *s, int *i, char *charset)
{
	int			curr_chr;
	static int	curr_w;

	if (*i == -1)
	{
		curr_w = 0;
		return (0);
	}
	curr_chr = 0;
	while (s[*i + curr_chr] && !is_in_charset(s[*i + curr_chr], charset))
		curr_chr++;
	ary[curr_w] = ft_strndup(s + *i, curr_chr);
	if (!ary[curr_w])
		return (0);
	*i += curr_chr - 1;
	curr_w++;
	return (curr_w);
}

char	**ft_split(char *s, char *charset)
{
	int		i;
	int		curr_w;
	char	**ary;

	if (s == NULL)
		return ((char **) 0);
	ary = (char **)ft_calloc((get_word_cnt(s, charset) + 1), sizeof(char *));
	if (!ary)
		return (NULL);
	i = -1;
	curr_w = 0;
	while (s[++i])
	{
		if (is_in_charset(s[i], charset))
			continue ;
		curr_w = get_next_word(ary, s, &i, charset);
		if (!curr_w)
			return ((char **)free_ary(ary));
	}
	ary[curr_w] = NULL;
	i = -1;
	curr_w = get_next_word(ary, s, &i, charset);
	return (ary);
}
