/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:05:31 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:05:33 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_execve_fails(void)
{
	close(0);
	close(1);
	perror("Error trying to execute execve.");
	exit(1);
}

void	ft_execute(char **argv, char **env, int fd, int out)
{
	char	**cmd;
	int		stat;
	int		pid;

	cmd = ft_get_cmd(argv[0], env, fd, out);
	pid = ft_fork(NULL, fd, out, cmd);
	if (pid == 0)
	{
		dup2(out, 1);
		if (out != 1)
			close(out);
		dup2(fd, 0);
		if (fd != 0)
			close(fd);
		execve(cmd[0], cmd, env);
		ft_execve_fails();
	}
	close(out);
	close(fd);
	stat = 0;
	waitpid(pid, &stat, 0);
	ft_freestrs(cmd);
	if (WIFEXITED(stat))
		exit(WEXITSTATUS(stat));
	exit(0);
}
