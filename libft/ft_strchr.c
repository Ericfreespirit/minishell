/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:35:10 by eriling           #+#    #+#             */
/*   Updated: 2021/07/28 15:07:39 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ss;
	int		len;
	int		i;

	i = 0;
	ss = (char *)s;
	len = ft_strlen(ss);
	while (i <= len)
	{
		if (ss[i] == (char)c)
			return (&ss[i]);
		i++;
	}
	return (NULL);
}
