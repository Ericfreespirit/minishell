/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_backtracking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:41:27 by eriling           #+#    #+#             */
/*   Updated: 2021/11/17 16:47:25 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hdoc	*cpy_hdoc(t_redir *tmp)
{
	t_hdoc	*hdoc;

	hdoc = calloc(1, sizeof(t_hdoc));
	if (hdoc == NULL)
		return (NULL);
	hdoc->end = ft_strdup(tmp->file);
	hdoc->next = NULL;
	return (hdoc);
}

int	create_hdoc_list_node(t_ast *node)
{
	t_redir	*tmp;
	t_hdoc	*curr;

	tmp = node->redir;
	while (tmp != NULL)
	{
		if (tmp->index == 3)
		{
			if (node->hdoc == NULL)
				node->hdoc = cpy_hdoc(tmp);
			else
			{
				curr = node->hdoc;
				while (curr->next != NULL)
					curr = curr->next;
				curr->next = cpy_hdoc(tmp);
			}
		}
		tmp = tmp->next;
	}
	return (fork_rdl_hdoc(node));
}

/*
	Backtracking readline hdoc
*/
int	hdoc_backtracking(t_ast *node)
{
	if (node->left != NULL)
		hdoc_backtracking(node->left);
	if (node->right != NULL)
		hdoc_backtracking(node->right);
	if (node != NULL)
	{
		if (create_hdoc_list_node(node) == 1)
			sg()->stop = 1;
	}
	return (0);
}
