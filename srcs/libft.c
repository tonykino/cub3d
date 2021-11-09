#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	dst = malloc(count * size);
	if (dst == NULL)
	{
		return (NULL);
	}
	ft_bzero(dst, count * size);
	return (dst);
}


int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	// printf("red = %d, green = %d, blue = %d\n", red, green, blue);
	return (red << 16 | green << 8 | blue);
}

void normalize_angle(float *angle)
{
	*angle = remainder(*angle, 2 * M_PI);
	if (*angle < 0)
	{
		*angle += 2 * M_PI;
	}
}

float dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

bool		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1 && s1[i] && s2 && s2[i] && s1[i] == s2[i])
		i++;
	return ((bool)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	while (s2[i])
	{
		if (s2[i] == (unsigned char)c)
		{
			return ((char *)(s2 + i));
		}
		i++;
	}
	if (s2[i] == (unsigned char)c)
	{
		return ((char *)(s2 + i));
	}
	else
	{
		return (NULL);
	}
}

bool		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool is_number(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*c_dst;
	unsigned char	*c_src;

	i = 0;
	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	if (c_dst == NULL && c_src == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (dst);
}


// static int	is_in_set(char c, char const *set)
// {
// 	size_t	i;

// 	i = 0;
// 	while (set && set[i])
// 	{
// 		if (c == set[i])
// 		{
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }


// char		*ft_strtrim(char *s1, char *set)
// {
// 	size_t	start;
// 	size_t	len;
// 	char	*dst;

// 	if (s1 == NULL)
// 		return (NULL);
// 	start = 0;
// 	while (is_in_set(s1[start], set))
// 		start++;
// 	len = ft_strlen(s1 + start);
// 	while (len > 0 && is_in_set(s1[start + len - 1], set))
// 		len--;
// 	dst = malloc(len + 1);
// 	if (dst == NULL)
// 		return (NULL);
// 	ft_memcpy(dst, s1 + start, len);
// 	dst[len] = '\0';
// 	free(s1);
// 	return (dst);
// }