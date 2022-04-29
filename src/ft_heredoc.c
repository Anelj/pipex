/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:05:50 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:05:52 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_get_saved_out(int fds[2], int out, int i)
{
	int	saved_out;

	saved_out = 0;
	if (i > 1)
		ft_pipe(fds, -1, out, &saved_out);
	else
		saved_out = out;
	return (saved_out);
}

void	ft_error_processing_heredoc(int flag, char *buffer, int out)
{
	close(out);
	free(buffer);
	if (!flag)
	{
		perror("Error while heredoc processing.");
		exit(1);
	}
	exit(0);
}

int	ft_getcbytes(char *buf, size_t nbytes, char *buffer, int out)
{
	int	cbytes;

	write(1, "pipe heredoc> ", 14);
	cbytes = read(0, buf, nbytes);
	if (cbytes < 0)
		ft_error_processing_heredoc(0, buffer, out);
	buf[cbytes] = '\0';
	return (cbytes);
}

void	ft_proccess_heredoc(int out, char *limiter)
{
	int		cbytes;
	char	*buffer;
	char	*buf;
	size_t	nbytes;
	int		lim_size;

	buffer = ft_getbuffer(out);
	buf = buffer;
	nbytes = BUFFER_SIZE;
	lim_size = ft_strlen(limiter);
	while (1)
	{
		cbytes = ft_getcbytes(buf, nbytes, buffer, out);
		if (!cbytes || (cbytes - 1 == lim_size
				&& !ft_strncmp(limiter, buf, cbytes - 1)))
		{
			write(out, buffer, buf - buffer);
			ft_error_processing_heredoc(1, buffer, out);
		}
		nbytes = nbytes - cbytes;
		ft_fullbuffer(nbytes, out, buffer, limiter);
		buf = buf + cbytes;
	}
}

/*
void	ft_proccess_heredoc1(int out, char *limiter)
{
	char	*s;
	size_t	len;
	int		flag;

	flag = 0;
	write(1, "pipe heredoc> ", 14);
	s = get_next_line(0);
	while (s)
	{
		len = ft_strlen(s);
		s[len - 1] = '\0';
		if (!ft_strncmp(limiter, s, len))
		{
			flag = 1;
			close(out);
			close(0);
		} else
		{
			(s)[len - 1] = '\n';
			printf("before write\n");
			int b = write(out, s, len);
				printf("smth < 0 %i\n", b);
			if (errno == EPIPE || errno  == SIGPIPE)
			{
				printf("SIG\n");
				close(0);
			}
				//printf("sigpipe\n");
			printf("after write");
			//if (errno != 0)
				printf("%s\n", strerror(errno));
		}
		free(s);
		if (!flag)
			write(1, "pipe heredoc> ", 14);
		s = get_next_line(0);
		printf("%s read s\n", s);
	}
	printf("%s read s\n", s);
	ft_error_processing_heredoc(flag, s, out);
}
*/

void	ft_heredoc(int i, char **argv, char **env, char *limiter)
{
	int	out;
	int	fds[2];
	int	saved_in;
	int	saved_out;
	int	a;

	out = ft_open(argv[i + 1], 0, 1, -1);
	a = 0;
	saved_in = 0;
	while (i > 0)
	{
		saved_out = ft_get_saved_out(fds, out, i);
		if (ft_fork(fds, -1, out, NULL) == 0)
		{
			if (i > 1)
				close(fds[0]);
			if (!a)
				ft_proccess_heredoc(saved_out, limiter);
			else
				ft_execute(argv + 1 + a, env, saved_in, saved_out);
		}
		a++;
		i = ft_pipe_helper(&saved_in, saved_out, fds[0], i);
	}
}
