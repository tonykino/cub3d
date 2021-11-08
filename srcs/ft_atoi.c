#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	ignore_whitespaces(const char *str)
{
	int i;

	i = 0;
	while (is_whitespace(str[i]))
	{
		i++;
	}
	return (i);
}

int			ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned int	nb;

	i = ignore_whitespaces(str);
	nb = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (sign * nb);
}
