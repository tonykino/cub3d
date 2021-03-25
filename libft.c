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
