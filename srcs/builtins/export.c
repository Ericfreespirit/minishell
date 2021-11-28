/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:42:19 by eriling           #+#    #+#             */
/*   Updated: 2021/11/03 15:44:14 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_display(char ***envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	sorting_envp(*envp);
	while ((*envp)[i])
	{
		if ((*(*envp)[i]) != '_')
		{
			write(1, "declare -x ", 11);
			while ((*envp)[i][j] && (*envp)[i][j - 1] != '=')
				write(1, &((*envp)[i][j++]), 1);
			write(1, "\"", 1);
			while ((*envp)[i][j])
				write(1, &((*envp)[i][j++]), 1);
			j++;
			ft_putendl_fd("\"", 1);
			j = 0;
		}
		i++;
	}
}

// export var_name=var_val
void	add_var_env(char *var_name, char *var_val, char ***envp)
{
	int		len;
	char	*tmp;

	unset(var_name, envp);
	len = 0;
	while ((*envp)[len])
		len++;
	*envp = ft_realloc(*envp, (sizeof(char *) * (len + 2)),
			sizeof(char *) * len);
	if (*envp == NULL)
		return ;
	(*envp)[len] = ft_calloc(sizeof(char), ((ft_strlen(var_name)
					+ (ft_strlen(var_val))) + 2));
	if ((*envp)[len] == NULL)
	{
		free_arr_poin(*envp);
		return ;
	}
	tmp = ft_strjoin(var_name, "=");
	if (var_val != NULL)
		tmp = ft_strjoinfree2(&tmp, &var_val, 0);
	(*envp)[len] = ft_strcpy((*envp)[len], tmp);
	free(tmp);
}

// export var_name+=var_val
void	conc_var_env(char *var_name, char *var_val, char ***envp)
{
	int	i;
	int	j;

	i = 0;
	if (is_var_env(var_name, envp) == 0 || var_val == NULL)
	{
		add_var_env(var_name, var_val, envp);
		return ;
	}
	while ((*envp)[i])
	{
		j = 0;
		while ((*envp)[i][j] && (*envp)[i][j] != '=')
			j++;
		if (strncmp((*envp)[i], var_name, j) == 0)
			(*envp)[i] = ft_strjoinfree((*envp)[i], var_val, 0);
		i++;
	}
}

int	export(char *var_name, char *var_val, int oper, char ***envp)
{
	if (var_name == NULL || ft_isalpha(*var_name) == 0)
		return (1);
	else if (oper == PLUS_EQUAL)
		conc_var_env(var_name, var_val, envp);
	else if (oper == EQUAL)
		add_var_env(var_name, var_val, envp);
	return (0);
}

int	launch_export(char **arg, char ***envp)
{
	int		i;
	int		operation;
	char	*var_name;
	char	*var_val;
	int		error;

	i = 1;
	error = 0;
	if (arg[i] == NULL)
		export_display(envp);
	while (arg[i])
	{
		ft_split_export(&var_name, &var_val, &operation, arg[i]);
		if (export(var_name, var_val, operation, envp) == 1)
			error = 1;
		free(var_name);
		free(var_val);
		i++;
	}
	if (error == 1)
		return (str_error("minishell : export : invalid variable", 1, 2));
	sg()->ret_exit = 0;
	return (0);
}
