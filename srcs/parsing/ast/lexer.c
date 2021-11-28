/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:23:52 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:40:38 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_lexical_field(char **lex_fi, int ret)
{
	int	i;

	i = 0;
	if (lex_fi == 0)
		return (1);
	while (lex_fi[i])
	{
		free(lex_fi[i]);
		i++;
	}
	free(lex_fi);
	return (ret);
}

/* 
	Count all token in the line
*/
int	count_token(char *line)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		len = len_token(line + i);
		if (len > 0)
		{
			count++;
			i += len;
		}
		else
			return (-1);
		while (line[i] == ' ')
			i++;
	}
	return (count);
}

/*
	Calloc array of string: sg()->lex_fi
*/
int	alloc_lexical_field(char *line)
{
	int	i;

	i = count_token(line);
	if (i == -1)
		return (1);
	(sg()->lex_fi) = ft_calloc(i + 1, sizeof(char *));
	if (sg()->lex_fi == NULL)
		return (1);
	return (0);
}

/*
	Store all token in a array of string: sg()->lex_fi
*/
int	get_lexical_field(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (alloc_lexical_field(line) == 1)
		return (1);
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (len_token(line + i) > 0)
		{
			(sg()->lex_fi[j]) = ft_substr(line + i, 0, len_token(line + i));
			if (sg()->lex_fi[j] == NULL)
				return (1);
			j++;
			i += len_token(line + i);
		}
		else
			return (free_lexical_field(sg()->lex_fi, 1));
		while (line[i] == ' ')
			i++;
	}
	return (0);
}
