/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 11:20:04 by eriling           #+#    #+#             */
/*   Updated: 2021/08/18 14:57:17 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// save var_name before "=" or "+="
char	*varname_export(char *str)
{
	int		i;
	int		len;
	char	*var_name;

	i = 0;
	len = 0;
	var_name = NULL;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	if (str[len] == '+' && str[len + 1] != '=')
		return (NULL);
	else if (len != 0)
	{
		var_name = ft_calloc(sizeof(char), (len + 1));
		if (var_name == NULL)
			return (NULL);
	}
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

// save var_val after "=" or "+="
char	*varval_export(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*var_val;

	i = 0;
	j = 0;
	len = 0;
	var_val = NULL;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	while (str[i + len])
		len++;
	if (len != 0)
	{
		var_val = ft_calloc(sizeof(char), (len + 1));
		if (var_val == NULL)
			return (NULL);
	}
	while (str[i])
		var_val[j++] = str[i++];
	return (var_val);
}

int	get_export_op(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			break ;
		else if (str[i] == '=')
			return (EQUAL);
		i++;
	}
	if (str[i] == '+')
	{
		if (str[i + 1] == '=')
			return (PLUS_EQUAL);
	}
	return (0);
}

void	ft_split_export(char **name, char **val, int *operation, char *arg)
{
	*name = varname_export(arg);
	*val = varval_export(arg);
	*operation = get_export_op(arg);
}
