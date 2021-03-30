#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <math.h>

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
float distance_between_points(float x1, float y1, float x2, float y2);
void normalize_angle(float *angle);
bool		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
// char		*ft_strtrim(char *s1, char *set);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char *str, char *charset);
int			ft_atoi(const char *str);
bool is_number(char *str);
bool		ft_isdigit(int c);

#endif
