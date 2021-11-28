/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_node_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:56:00 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 17:37:23 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Store redirection in a node
*/
int	store_node_redir(t_ast *node, char *str)
{
	t_redir	*tmp;

	tmp = node->redir;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		tmp->next = store_redir(str);
		if (tmp->next == NULL)
			return (1);
	}
	else
	{
		node->redir = store_redir(str);
		if (node->redir == NULL)
			return (1);
	}
	return (0);
}

char	*file_hdoc(char *str)
{
	int		i;
	int		c;
	char	*dest;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] != '\0' && is_quote(str[i]) == 0)
			c++;
		i++;
	}
	dest = calloc(c + 1, sizeof(char *));
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] != '\0' && is_quote(str[i]) == 0)
			dest[c++] = str[i];
		i++;
	}
	return (dest);
}

int	store_node_file(t_ast *node, char *str)
{
	t_redir	*curr;

	curr = node->redir;
	while (curr != NULL && curr->next != NULL)
		curr = curr->next;
	if (curr->index != 3)
		curr->file = ft_replace_token(str);
	else
		curr->file = file_hdoc(str);
	if (curr->file == NULL)
		return (1);
	return (0);
}

/*
	Store word in a node
*/
int	store_node_word(t_ast *node, char *str)
{
	char	*tmp;

	tmp = ft_replace_token(str);
	if (tmp == NULL)
		return (1);
	if (node->arg == NULL)
	{
		node->arg = ft_calloc(sizeof(char *), 2);
		if (node->arg == NULL)
			return (1);
		node->arg[0] = tmp;
	}
	else
		node->arg = realloc_node_arg(node->arg, tmp);
	return (0);
}

/*
	Store redirection, file or word in a node
*/
void	store_node_data(t_ast *node, char *str, int type)
{
	if (type == REDIRECTION)
	{
		if (store_node_redir(node, str) == 1)
			return (err_msg("Error malloc", 2, 1));
	}
	else if (type == WORD)
	{
		if (store_node_word(node, str) == 1)
			return (err_msg("Error malloc", 2, 1));
	}
	else if (type == FILE)
	{
		if (store_node_file(node, str) == 1)
			return (err_msg("Error malloc", 2, 1));
	}
}
