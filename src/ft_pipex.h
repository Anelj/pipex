/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:06:10 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:06:11 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# define BUFFER_SIZE 8000

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

void	ft_pipex(int argc, char **argv, char **env);

int		ft_strncmp(const char *ss1, const char *ss2, size_t n);

char	*ft_strjoin1(const char *s1, const char *s2);

char	**ft_split(char const *s, char c);

char	**ft_splitpath(char const *s, char c);

size_t	ft_strlen(const char *s);

char	*ft_path(char *cmdname, char **env);

void	ft_freestrs(char **s);

void	ft_heredoc(int i, char **argv, char **env, char *limiter);

void	ft_standard_pipe(int i, char **argv, char **env, int saved_in);

int		ft_open(char *file, int toread, int toappend, int toclose);

int		ft_fork(int fds[2], int in, int out, char **cmd);

int		ft_pipe_helper(int *in, int out, int fds0, int i);

void	ft_pipe(int *fds, int in, int out, int *saved_out);

void	ft_execute(char **argv, char **env, int fd, int out);

int		ft_pipe_helper(int *in, int out, int fds0, int i);

char	**ft_get_cmd(char *string, char **env, int fd, int out);

char	*ft_getbuffer(int out);

void	ft_error_processing_heredoc(int flag, char *buffer, int out);

char	**ft_split_freestrs(char **strs, char **ss);

int		ft_quotes(const char **str);

void	ft_fullbuffer(size_t nbytes, int out, char *buffer, char *limiter);

void	ft_proccess_heredoc(int out, char *limiter);

#endif
