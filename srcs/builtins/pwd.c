/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:42:12 by ladawi            #+#    #+#             */
/*   Updated: 2021/11/30 14:16:30 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*value;
	char	s[MAX_PATH];

	value = getcwd(s, MAX_PATH);
	if (value == NULL)
	{
		value = get_varname_val("PWD", sg()->env);
		if (value == NULL)
		{
			ft_putendl_fd("minishell: PWD: no path", STDERR);
			return (0);
		}
	}
	write(1, value, ft_strlen(value));
	write(1, "\n", 1);
	sg()->ret_exit = 0;
	return (0);
}
