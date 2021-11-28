/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:22:56 by eriling           #+#    #+#             */
/*   Updated: 2021/06/24 15:05:11 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*dest;

	if (!s)
		return ;
	dest = ft_strjoin(s, "\n");
	write(fd, dest, ft_strlen(dest));
	free(dest);
}
