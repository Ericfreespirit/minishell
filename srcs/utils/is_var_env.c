/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 11:36:22 by eriling           #+#    #+#             */
/*   Updated: 2021/08/18 14:57:26 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sorting_envp(char **envp)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (envp[i])
	{
		while (envp[j])
		{
			if (ft_strcmp(envp[j], envp[i]) < 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}

int	is_var_env(char *var_name, char ***envp)
{
	int	i;
	int	j;

	i = 0;
	while ((*envp)[i])
	{
		j = 0;
		while ((*envp)[i][j] && (*envp)[i][j] != '=')
			j++;
		if (ft_strncmp((*envp)[i], var_name, j) == 0)
			return (1);
		i++;
	}
	return (0);
}
