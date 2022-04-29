/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:07:05 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:07:07 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return (l);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		l;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (char *) dest;
	s = (const char *) src;
	l = 0;
	while (l < n)
	{
		d[l] = s[l];
		l++;
	}
	return (dest);
}

static size_t	ft_max_size(void)
{
	size_t	max_size;
	size_t	bits;

	max_size = 1;
	bits = sizeof(size_t) * 8;
	while (bits--)
	{
		max_size = max_size * 2;
	}
	return (max_size - 1);
}

char	*ft_strjoin1(const char *s1, const char *s2)
{
	size_t	max_size;
	size_t	len;
	size_t	len1;
	size_t	len2;
	char	*s;

	max_size = ft_max_size();
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((len1 != max_size) && ((max_size - len1 - 1) >= len2))
		len = len1 + len2;
	else
		return (NULL);
	s = (char *) malloc(len + 1);
	if (s == NULL)
		return (NULL);
	ft_memcpy((void *)s, (const void *)s1, len1);
	ft_memcpy((void *)(s + len1), (const void *)s2, len2 + 1);
	return (s);
}
