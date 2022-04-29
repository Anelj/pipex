/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_helper_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <mgoliath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:02:34 by mgoliath          #+#    #+#             */
/*   Updated: 2021/12/23 19:02:36 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

char	*ft_getbuffer(int out)
{
	char	*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		ft_error_processing_heredoc(0, buffer, out);
	buffer[BUFFER_SIZE] = '\0';
	return (buffer);
}

void	ft_fullbuffer(size_t nbytes, int out, char *buffer, char *limiter)
{
	if (nbytes == 0)
	{
		write(out, buffer, BUFFER_SIZE);
		ft_proccess_heredoc(out, limiter);
	}
}
