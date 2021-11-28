/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:32:20 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:44:01 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ast(t_ast *node)
{
	t_redir	*tmp;

	if (node->right != NULL)
		check_ast(node->right);
	if (node->left != NULL)
		check_ast(node->left);
	if (node != NULL)
	{
		tmp = node->redir;
		while (tmp != NULL)
		{
			if (tmp->file == NULL)
				return (str_error(
						"minishell: Aucun fichier ou dossier de ce type",
						1, 2));
			tmp = tmp->next;
		}
	}
	return (0);
}
