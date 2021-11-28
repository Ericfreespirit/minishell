/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:45:33 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:44:57 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' )
		return (1);
	return (0);
}

int	is_redirection(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, "<") || !ft_strcmp(s, ">>")
		|| !ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	is_word(char *s)
{
	if (s == 0 || is_redirection(s) == 1 || ft_strcmp(s, "|") == 0)
		return (0);
	return (1);
}
