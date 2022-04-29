/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:06:33 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:06:35 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	ft_wordlen(char const *s, char c)
{
	int	l;

	l = 0;
	while (*s && *s != c)
	{
		l++;
		s++;
	}
	while (*s && *s != ' ')
	{
		s++;
		l++;
	}
	if (c != ' ')
		l--;
	return (l);
}

static int	ft_fill(char **strs, char const **s_tosplit, char c)
{
	int			l;
	int			i;
	char const	*s;

	s = *s_tosplit;
	l = ft_wordlen(s, c);
	if (l == 0)
		return (0);
	*strs = (char *)malloc(sizeof(char) * (l + 1));
	if (*strs == NULL)
	{
		return (-1);
	}
	(*strs)[l] = '\0';
	i = 0;
	while (l--)
	{
		(*strs)[i] = *s;
		i++;
		s++;
	}
	*s_tosplit = s;
	return (1);
}

static char	**ft_fillstrs(char **ss, char const *s, char c, int l)
{
	int		i;
	char	**strs;

	strs = ss;
	while (l-- && *s)
	{
		while (*s == ' ')
			s++;
		if (*s == 39 || *s == 34)
		{
			c = *s;
			s++;
		}
		i = ft_fill(strs, &(s), c);
		if (i == 1)
			strs++;
		else if (i == -1)
			return (ft_split_freestrs(strs, ss));
	}
	return (ss);
}

static int	ft_countstrs(char const *s, char c)
{
	int	l;
	int	lw;

	if (!*s)
		return (0);
	l = 0;
	lw = 0;
	while (*s)
	{
		if (*s == 39 || *s == 34)
			lw = ft_quotes(&s);
		else if (*s == c && lw != 0)
		{
			l++;
			lw = 0;
		}
		else if (*s != c)
			lw++;
		if (lw < 0)
			return (lw);
		s++;
	}
	if (lw != 0)
		l++;
	return (l);
}

char	**ft_split(char const *s, char c)
{
	int		l;
	char	**strs;

	l = ft_countstrs(s, c);
	if (l < 0)
		return (NULL);
	strs = (char **)malloc(8 * (l + 1));
	if (strs == NULL)
		return (NULL);
	strs[l] = NULL;
	return (ft_fillstrs(strs, s, c, l));
}
