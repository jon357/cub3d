/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:22 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 15:13:41 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_bzero(void *ptr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t newsize, size_t oldsize)
{
	char	*newptr;

	if (ptr == NULL)
	{
		return (malloc(newsize));
	}
	if (newsize <= oldsize)
	{
		return (ptr);
	}
	newptr = malloc(newsize);
	if (newptr == NULL)
	{
		return (NULL);
	}
	ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}
