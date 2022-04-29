/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:04:49 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:04:51 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

static int	ft_strnicmp(
		unsigned char *s1, unsigned char *s2, size_t i, size_t n)
{
	if (n != i)
	{
		if (s1[i] == s2[i])
			return (0);
		else if (s1[i] > s2[i])
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	ft_strncmp(const char *ss1, const char *ss2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *) ss1;
	s2 = (unsigned char *) ss2;
	i = 0;
	while (n != i && s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] > s2[i])
		{
			return (1);
		}
		if (s1[i] < s2[i])
		{
			return (-1);
		}
		i++;
	}
	return (ft_strnicmp(s1, s2, i, n));
}
