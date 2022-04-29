/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:01:40 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:01:43 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

char	*ft_find_cmdpath_inpath(char *envPATH, char *cmdname)
{
	char	**paths;
	char	*cmdpath;
	int		i;

	paths = ft_splitpath(envPATH + 5, ':');
	i = 0;
	while (paths && paths[i])
	{
		cmdpath = ft_strjoin1(paths[i], cmdname);
		if (cmdpath && !access(cmdpath, 1))
		{
			free(cmdname);
			ft_freestrs(paths);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	ft_freestrs(paths);
	return (NULL);
}

void	ft_freestrs(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	*ft_path(char *cmdname, char **env)
{
	if (!access(cmdname, 1))
		return (cmdname);
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			return (ft_find_cmdpath_inpath(*env, cmdname));
		env++;
	}
	return (NULL);
}

char	**ft_get_cmd(char *string, char **env, int fd, int out)
{
	char	**cmd;
	char	*execcmd;

	cmd = ft_split(string, ' ');
	if (cmd)
		execcmd = ft_path(cmd[0], env);
	if (!cmd || !execcmd)
	{
		ft_freestrs(cmd);
		close(fd);
		close(out);
		perror("Error trying to split commands or find it in the PATH.");
		exit(1);
	}
	cmd[0] = execcmd;
	return (cmd);
}
