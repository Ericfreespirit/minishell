/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:51:19 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:44:45 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_arg_arr(char **arg, char **arr)
{
	free_arg(arg);
	free_arg(arr);
	return (NULL);
}

char	**free_arg(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (NULL);
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return (NULL);
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file != NULL)
			free(tmp->file);
		free(tmp);
	}	
}

int	free_ast(t_ast *node, int ret)
{
	int	i;

	i = 0;
	if (node != NULL)
	{
		if (node->left != NULL)
			free_ast(node->left, 0);
		if (node->right != NULL)
			free_ast(node->right, 0);
		free_arg(node->arg);
		if (node->hdoc != NULL)
			free_hdoc_node(node->hdoc);
		free_redir(node->redir);
		free(node);
	}
	return (ret);
}
