/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_standard_pipe_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:03:59 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:04:02 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

void	ft_standard_pipe(int i, char **argv, char **env, int saved_in)
{
	int	out;
	int	fds[2];
	int	saved_out;
	int	a;

	out = ft_open(argv[i - 1], 0, 0, saved_in);
	i = i - 3;
	a = 0;
	while (i > 0)
	{
		if (i > 1)
			ft_pipe(fds, saved_in, out, &saved_out);
		else
			saved_out = out;
		if (ft_fork(fds, saved_in, out, NULL) == 0)
		{
			if (i > 1)
				close(fds[0]);
			ft_execute(argv + 2 + a, env, saved_in, saved_out);
		}
		a++;
		i = ft_pipe_helper(&saved_in, saved_out, fds[0], i);
	}
}
