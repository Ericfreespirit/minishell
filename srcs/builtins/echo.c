/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 03:22:25 by eriling           #+#    #+#             */
/*   Updated: 2021/09/22 17:31:43 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char **arg)
{
	int	i;

	i = 0;
	if ((*arg)[i] != 0 && ft_strncmp(*arg, "-n", 2) == 0)
	{
		i++;
		while ((*arg)[i] && (*arg)[i] == 'n')
			i++;
		if ((*arg)[i] == '\0')
			return (1);
	}
	return (0);
}

void	echo(char **arg)
{
	int		i;
	int		n;

	n = 0;
	i = 1;
	while (arg[i] && is_flag(&arg[i]) == 1)
	{
		n = 1;
		i++;
	}
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1] != 0)
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
	sg()->ret_exit = 0;
}
