/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:06:02 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:06:03 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_pipe_helper(int *in, int out, int fds0, int i)
{
	if (out != 1)
		close(out);
	if (in != 0)
		close(*in);
	if (i > 1)
		*in = fds0;
	return (i - 1);
}

void	ft_pipe(int *fds, int in, int out, int *saved_out)
{
	int	stat;

	if (pipe(fds) < 0)
	{
		stat = 0;
		close(in);
		close(out);
		while (wait(&stat))
			stat++;
		perror("Error trying to create a pipe.");
		exit(1);
	}
	*saved_out = fds[1];
}

int	ft_open(char *file, int toread, int toappend, int toclose)
{
	int	fd;

	if (!toread && !toappend)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!toread && toappend)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (toread)
		fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		if (toclose >= 0)
			close(toclose);
		perror("Error trying to open file.");
		exit(1);
	}
	return (fd);
}

int	ft_fork(int fds[2], int in, int out, char **cmd)
{
	int	fd;
	int	stat;

	fd = fork();
	if (fd < 0)
	{
		if (fds)
		{
			close(fds[0]);
			close(fds[1]);
		}
		if (in > 0)
			close(in);
		if (out > 0)
			close(out);
		while (wait(&stat) > 0)
			stat++;
		if (cmd)
			ft_freestrs(cmd);
		perror("Error trying to make fork.");
		exit(1);
	}
	return (fd);
}
