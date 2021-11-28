/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:21:50 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:23:43 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_hdoc(t_redir *redir)
{
	if (redir == NULL)
		return (1);
	redir = redir->next;
	while (redir != NULL)
	{
		if (redir->index == 3)
			return (0);
		redir = redir->next;
	}
	return (1);
}

int	add_fd_redir(t_ast *node, int fd)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir != NULL)
	{
		if (redir->index == 3 && is_last_hdoc(redir) == 1)
		{
			redir->hdoc_fd = fd;
			return (0);
		}
		redir = redir->next;
	}
	return (1);
}
