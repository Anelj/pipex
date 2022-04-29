/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:07:33 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:07:36 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_getexitcode(int stat, int exit_code)
{
	if (WIFSIGNALED(stat))
		exit_code = WTERMSIG(stat);
	if (WIFEXITED(stat))
	{
		if (WEXITSTATUS(stat))
			exit_code = WEXITSTATUS(stat);
	}
	return (exit_code);
}

void	ft_pipex(int argc, char **argv, char **env)
{
	int		in;
	char	*limiter;
	int		exit_code;
	int		stat;

	if (!ft_strncmp("here_doc", *(argv + 1), 9))
	{
		in = 0;
		limiter = argv[2];
		ft_heredoc(argc - 3, argv + 1, env, limiter);
	}
	else
	{
		in = ft_open(argv[1], 1, 0, -1);
		ft_standard_pipe(argc, argv, env, in);
	}
	stat = 0;
	exit_code = 0;
	while (wait(&stat) > 0)
		exit_code = ft_getexitcode(stat, exit_code);
	exit(exit_code);
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
		exit(1);
	ft_pipex(argc, argv, env);
	return (0);
}
