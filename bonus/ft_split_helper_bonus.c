/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_helper_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:03:32 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:03:33 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

static int	ft_quotes_helper(int lw, const char **str, const char *s, char c)
{
	if (!lw)
		return (-1);
	if (*str != s)
		*str = s - 1;
	if (**str != c)
		return (-1);
	return (lw);
}

char	**ft_split_freestrs(char **strs, char **ss)
{
	*strs = NULL;
	strs = ss;
	while (*strs)
		free(*strs++);
	free(ss);
	return (NULL);
}

int	ft_quotes(const char **str)
{
	const char	*s;
	int			lw;
	char		c;

	s = *str;
	lw = 0;
	c = ' ';
	if (*s && (*s == 39 || *s == 34))
	{
		c = *s;
		s++;
	}
	while (*s && *s != c)
	{
		lw++;
		s++;
	}
	while (*s && *s != ' ')
	{
		lw++;
		s++;
	}
	return (ft_quotes_helper(lw, str, s, c));
}
