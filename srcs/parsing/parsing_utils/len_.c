/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:46:25 by eriling           #+#    #+#             */
/*   Updated: 2021/11/05 16:21:46 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Get len of string in an array of string
*/
int	len_arr(char **arg)
{
	int	i;

	i = 0;
	if (arg == 0)
		return (0);
	while (arg[i])
		i++;
	return (i);
}

/*
	Get len of string unquoted
*/
int	len_string(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_quote(str[len]))
		len++;
	return (len);
}

/*
	Get len of a string quoted
*/
int	len_string_quoted(char *line, char quote)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	return (-1);
}

/*
	Get len of operator [>], [>>], [<], [<<], [|]
*/
int	len_operator(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '|')
		return (i + 1);
	else if (line[i] == '>' || line[i] == '<')
	{
		i++;
		if ((line[i - 1] == '>' && line[i] == '>')
			|| (line[i - 1] == '<' && line[i] == '<'))
			return (i + 1);
	}
	return (i);
}

/* 
	Get len of one token
*/
int	len_token(char *line)
{
	int	i;

	i = 0;
	if (is_operator(line[i]))
		return (i + len_operator(line + i));
	while (line[i] && line[i] != '\n' && line[i] != ' '
		&& !is_operator(line[i]))
	{
		if (is_quote(line[i]))
		{
			if (len_string_quoted(line + i, line[i]) > 0)
				i += len_string_quoted(line + i, line[i]);
			else
				return (0);
		}
		if (line[i] && line[i] != '\n' && line[i] != ' '
			&& !is_quote(line[i]) && !is_operator(line[i]))
			i++;
	}
	return (i);
}
