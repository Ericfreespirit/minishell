/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:27:25 by eriling           #+#    #+#             */
/*   Updated: 2021/11/05 16:21:47 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	There is 4 types of string in a token:
	- double quoted string
	- single quoted string
	- string begin with $
	- unquoted string
	A token is composed of one or multiple types of string.
*/

/*
	Return str expanded
*/
char	*get_exp(char **str)
{
	int		len;
	char	*dest;
	char	*var_name;

	len = 0;
	(*str)++;
	if (**str == 0)
		return (ft_strdup("$"));
	else if (is_quote(**str))
		return (ft_strdup(""));
	else if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(sg()->ret_exit));
	}
	while ((*str)[len] && (*str)[len] != ' ' && !is_quote((*str)[len])
		&& (*str)[len] != '$')
		len++;
	var_name = ft_substr(*str, 0, len);
	*str += len;
	dest = ft_strdup(get_varname_val(var_name, sg()->env));
	free(var_name);
	return (dest);
}

/*
	Replace str by a str unquoted or/and expanded
*/
char	*ft_replace_str(char *str)
{	
	char	*dest;
	char	*tmp;
	int		i;

	dest = NULL;
	i = 0;
	while (*str)
	{
		if (*str == '$')
			tmp = get_exp(&str);
		else
		{
			i = 0;
			while (str[i] && str[i] != '$')
				i++;
			tmp = ft_substr(str, 0, i);
			str += i;
		}
		dest = ft_strjoinfree2(&dest, &tmp, 2);
	}
	return (dest);
}

/*
	Store each str in this token expanded and unquoted 
*/
char	*store_exp_unq(char **str, char type)
{
	int		len;
	char	*dest;
	char	*tmp;

	len = 0;
	dest = NULL;
	tmp = NULL;
	if (type == '\'' || type == '\"')
		len = len_string_quoted(*str, type);
	else if (type == 0)
		len = len_string(*str);
	if (type == '\'')
		dest = ft_substr(*str + 1, 0, len - 2);
	else if (type == '\"')
		tmp = ft_substr(*str + 1, 0, len - 2);
	else if (type == 0)
		tmp = ft_substr(*str, 0, len);
	if (type == 0 || type == '\"')
		dest = ft_replace_str(tmp);
	if (tmp != NULL)
		free(tmp);
	*str += len;
	return (dest);
}

/*
	Specific case for $ string
*/
char	*store_dollar(char **str)
{
	char	*tmp;

	tmp = NULL;
	if ((*str)[1] == 0 || (*str)[1] == ' '
		|| (*str)[1] == '|')
	{
		(*str)++;
		tmp = ft_strdup("$");
	}
	else if ((*str)[1] == '$')
	{
		(*str) += 2;
		tmp = ft_strdup("");
	}
	else if (is_quote((*str)[1]))
	{
		(*str)++;
		tmp = ft_strdup("");
	}
	else
		tmp = store_exp_unq(str, 0);
	return (tmp);
}

/*
	Return the token entirely unquoted and expanded
*/
char	*ft_replace_token(char *str)
{
	char	*tmp;
	char	*dest;
	int		i;

	i = 0;
	dest = NULL;
	while (*str)
	{
		if (*str == '\'')
			tmp = store_exp_unq(&str, '\'');
		else if (*str == '\"')
			tmp = store_exp_unq(&str, '\"');
		else if (*str == '$')
			tmp = store_dollar(&str);
		else
			tmp = store_exp_unq(&str, 0);
		dest = ft_strjoinfree2(&dest, &tmp, 2);
		if (dest == NULL)
			return (NULL);
	}
	return (dest);
}
