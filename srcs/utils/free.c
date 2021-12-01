/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 16:04:38 by eriling           #+#    #+#             */
/*   Updated: 2021/12/01 09:11:54 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_rdl_str(void)
{
	free(sg()->str);
	sg()->str = NULL;
	return (NULL);
}

void	free_hdoc_node(t_hdoc *hdoc)
{
	t_hdoc	*tmp;
	t_hdoc	*curr;

	tmp = hdoc;
	while (tmp != NULL)
	{
		curr = tmp;
		if (curr->end != NULL)
			free(curr->end);
		tmp = tmp->next;
		free(curr);
	}
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_program(void)
{
	rl_clear_history();
	if (sg()->str != NULL)
		free(sg()->str);
	free_envp(sg()->env);
	free(sg());
}

void	free_hdoc_ast(t_ast *node)
{
	t_ast	*tmp;

	tmp = node;
	if (node->right != NULL)
		free_hdoc_ast(node->right);
	if (node->left != NULL)
		free_hdoc_ast(node->left);
	if (node != NULL)
		free_hdoc_node(node->hdoc);
}
