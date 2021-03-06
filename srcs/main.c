/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:18:05 by eriling           #+#    #+#             */
/*   Updated: 2021/12/01 09:11:10 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_envp(char ***envp)
{
	int		i;
	char	**cpy;

	i = 0;
	while ((*envp)[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	if (cpy == NULL)
		return (1);
	i = 0;
	while ((*envp)[i])
	{
		cpy[i] = malloc(sizeof(char) * (ft_strlen((*envp)[i]) + 1));
		if (cpy[i] == NULL)
		{
			cpy[i] = 0;
			free_arr_poin(cpy);
			return (1);
		}
		cpy[i] = ft_strcpy(cpy[i], (*envp)[i]);
		i++;
	}
	cpy[i] = 0;
	(*envp) = cpy;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int	status;

	(void)ac;
	(void)av;
	status = 0;
	sg()->str = NULL;
	sg()->prompt = "minishell> ";
	sg()->env = envp;
	if (malloc_envp(&(sg()->env)) == 1)
		return (str_error("Error malloc", 2, 1));
	launch_minishell();
	status = sg()->ret_exit;
	free_program();
	return (status);
}
