#include "cub3d.h"


static size_t	ft_intlen(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*dst;
	int		i;
	long	n;

	n = nb;
	i = ft_intlen(n);
	dst = (char *)malloc((i + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	dst[i--] = '\0';
	if (n == 0)
		dst[0] = '0';
	if (n < 0)
	{
		dst[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		dst[i] = '0' + (n % 10);
		n = n / 10;
		i--;
	}
	return (dst);
}
