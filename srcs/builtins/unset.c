/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:38:43 by eriling           #+#    #+#             */
/*   Updated: 2021/11/03 15:45:23 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_cpy_unset(char *var_name, char ***envp, char ***cpy, int i)
{
	int	j;

	j = 0;
	*cpy = calloc(sizeof(char *), (i + 1));
	if (*cpy == NULL)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (!to_find_varname((*envp)[i], var_name))
		{
			(*cpy)[j] = malloc(sizeof(char) * (ft_strlen((*envp)[i]) + 1));
			if ((*cpy)[j] == NULL)
			{
				(*cpy)[j] = 0;
				free_arr_poin(*envp);
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_alloc_unset(char *var_name, char ***envp, char ***cpy)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (var_name == NULL)
		return (1);
	while ((*envp)[i])
	{
		if (to_find_varname((*envp)[i], var_name))
			check = 1;
		i++;
	}
	if (check == 1)
	{
		alloc_cpy_unset(var_name, envp, cpy, i);
		return (0);
	}
	return (1);
}

int	unset(char *var_name, char ***envp)
{
	int		i;
	int		j;
	char	**cpy;

	if (check_alloc_unset(var_name, envp, &cpy) == 1)
		return (1);
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (to_find_varname((*envp)[i], var_name) == 0)
		{
			cpy[j] = ft_strcpy(cpy[j], (*envp)[i]);
			j++;
		}
		i++;
	}
	free_arr_poin(*envp);
	*envp = cpy;
	return (0);
}

int	launch_unset(char **arg, char ***envp)
{
	int		i;

	i = 1;
	if (arg[i] == NULL)
		return (0);
	while (arg[i])
	{
		if (unset(arg[i], envp) == 1)
		{
			err_msg("minishell : unset : invalid variable", 2, 1);
			return (1);
		}
		i++;
	}
	sg()->ret_exit = 0;
	return (0);
}
