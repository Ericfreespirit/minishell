/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:19:52 by ladawi            #+#    #+#             */
/*   Updated: 2021/11/25 11:28:02 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_findchar(const char c, char *tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[j])
	{
		if (tab[j] == c)
		{
			i++;
		}
		j++;
	}
	return (i);
}

int	to_find_varname(char *envp, char *to_find)
{
	int	i;

	i = 0;
	if (!envp || !to_find)
		return (0);
	while (to_find[i])
	{
		if (envp[i] != to_find[i])
			return (0);
		i++;
	}
	if (envp[i] == '=')
		return (1);
	return (0);
}

char	*get_varname_val(char *var_name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (to_find_varname(envp[i], var_name))
			return (&envp[i][ft_strlen(var_name) + 1]);
		i++;
	}
	return (NULL);
}

void	*ft_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	return (NULL);
}

void	free_line_exit(char *line)
{
	free(line);
	free_exit(2, 4);
}
