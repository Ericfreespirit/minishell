/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:38 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:48:39 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_error(char *s, int ret, int status)
{
	ft_putendl_fd(s, 2);
	sg()->ret_exit = status;
	return (ret);
}

char	*str_error2(char *s, char *ret, int status)
{
	ft_putendl_fd(s, 2);
	sg()->ret_exit = status;
	return (ret);
}

void	err_msg(char *str, int fd, int status)
{
	ft_putendl_fd(str, fd);
	sg()->ret_exit = status;
}
