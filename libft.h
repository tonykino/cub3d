#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue);

#endif
