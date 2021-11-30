/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:59:16 by eriling           #+#    #+#             */
/*   Updated: 2021/11/30 14:20:25 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_num(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == 0)
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str++) == 0)
			return (1);
	}
	return (0);
}

void	free_exit(int statut, int error)
{
	free_lexical_field(sg()->tmp, 0);
	free_ast(sg()->node, 0);
	if (error == 1)
		err_msg("minishell: exit: too many arguments", 2, 2);
	else if (error == 2)
		err_msg("minishell: exit: need numeric argument", 2, 2);
	else if (error == 3)
		err_msg("minishell: function failed", 2, statut);
	else if (error == 4)
		err_msg("minishell: parse error", 2, statut);
	if (error == 1 || error == 2)
		statut = 2;
	free_program();
	exit(statut);
}

int	ft_check_overflow(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
		i++;
	if (i >= 20)
		return (1);
	return (0);
}

void	ft_exit_status(t_ast *node)
{
	int	statut;

	statut = sg()->ret_exit;
	if (str_is_num(node->arg[1]) == 0)
	{
		if (ft_check_overflow(node->arg[1]) == 1)
		{
			free_exit(2, 2);
			return ;
		}
		statut = ft_atoi(node->arg[1]);
	}
	else
		free_exit(2, ERROR_NUM);
	if (statut >= 0 && statut <= 255)
		free_exit(statut, 0);
	else
	{
		if (statut < 0)
			statut = 255;
		else
			statut %= 256;
		free_exit(statut, 0);
	}
}

void	ft_exit(t_ast *node)
{
	int	i;

	i = 0;
	if (isatty(0))
		write(1, "exit\n", 5);
	if (node->arg == NULL)
		return (free_program());
	while (node->arg[i])
		i++;
	if (i > 2)
		free_exit(1, ERROR_ARG);
	else if (i == 2)
		ft_exit_status(node);
	else
		free_exit(0, 0);
}
