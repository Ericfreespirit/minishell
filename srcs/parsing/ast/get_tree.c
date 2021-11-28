/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:22:34 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:35:20 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->left = left;
	node->right = right;
	node->arg = NULL;
	node->redir = NULL;
	node->hdoc = NULL;
	return (node);
}

/*
	Create a command node
*/
t_ast	*create_cmd(void)
{
	t_ast	*node;
	int		i;

	i = 0;
	node = create_node(NULL, NULL);
	if (node == NULL)
		return (NULL);
	while (sg()->lex_fi[i] && sg()->lex_fi[i][0] != '|')
	{
		if (is_word(sg()->lex_fi[i]) == 1)
			store_node_data(node, sg()->lex_fi[i], WORD);
		else if (is_redirection(sg()->lex_fi[i]) == 1)
		{
			while (sg()->lex_fi[i] && is_redirection(sg()->lex_fi[i]) == 1)
				store_node_data(node, sg()->lex_fi[i++], REDIRECTION);
			if (sg()->lex_fi[i] && is_word(sg()->lex_fi[i]) == 1)
				store_node_data(node, sg()->lex_fi[i], FILE);
		}
		if (sg()->lex_fi[i] && sg()->lex_fi[i][0] != '|'
			&& !is_redirection(sg()->lex_fi[i]))
			i++;
	}
	sg()->lex_fi += i;
	return (node);
}

/*
	Create an Abstract syntax tree (Ast)
	An Ast is composed of one or multiple nodes
	Two type of node: pipe node or command node
	All pipe node have two branch composed of two node command
*/
int	get_tree(void)
{
	t_ast	*cmd;

	sg()->node = create_cmd();
	if (sg()->node == NULL)
		return (1);
	while (*sg()->lex_fi && !ft_strcmp(*sg()->lex_fi, "|"))
	{
		sg()->lex_fi += 1;
		cmd = create_cmd();
		if (cmd->arg == NULL && cmd->redir == NULL)
		{
			free_ast(cmd, 0);
			return (str_error("Error syntax command", 2, 1));
		}
		(sg()->node) = create_node(sg()->node, cmd);
		if (sg()->node == NULL)
			return (1);
		(sg()->node->arg) = ft_calloc(2, sizeof(char *));
		if (sg()->node->arg == NULL)
			return (1);
		sg()->node->arg[0] = ft_strdup("|");
	}
	return (0);
}
