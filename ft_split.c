#include "libft.h"

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

static size_t	get_word_cnt(char const *s, char *charset)
{
	size_t	i;
	size_t	count;

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

static char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = (char *)ft_calloc(n + 1, sizeof(char));
	if (dup == NULL)
	{
		return (NULL);
	}
	ft_memcpy(dup, s, n);
	return (dup);
}

static void	*free_ary(char **ary)
{
	size_t	i;

	i = 0;
	while (ary[i])
	{
		free(ary[i]);
		i++;
	}
	free(ary);
	return (NULL);
}

char	**ft_split(char *s, char *charset)
{
	size_t	i;
	size_t	curr_chr;
	size_t	curr_w;
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
		curr_chr = 0;
		while (s[i + curr_chr] && !is_in_charset(s[i + curr_chr], charset))
			curr_chr++;
		ary[curr_w] = ft_strndup(s + i, curr_chr);
		if (!ary[curr_w])
			return ((char **)free_ary(ary));
		i += curr_chr - 1;
		curr_w++;
	}
	ary[curr_w] = NULL;
	return (ary);
}
