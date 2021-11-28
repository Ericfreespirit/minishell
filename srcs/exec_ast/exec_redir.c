/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 15:44:21 by ladawi            #+#    #+#             */
/*   Updated: 2021/11/15 14:23:25 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->index == 1)
		fd = open(redir->file, O_RDONLY, 00777);
	else if (redir->index == 2)
		fd = open(redir->file, O_CREAT | O_RDWR | O_TRUNC, 00777);
	else if (redir->index == 3 && redir->hdoc_fd != -1)
		fd = redir->hdoc_fd;
	else if (redir->index == 4)
		fd = open(redir->file, O_CREAT | O_RDWR | O_APPEND, 00777);
	dup2(fd, (redir->index + 1) % 2);
	if (redir->next != NULL && redir->next->file != NULL)
	{
		close(fd);
		exec_redir(redir->next);
	}
	return (0);
}
