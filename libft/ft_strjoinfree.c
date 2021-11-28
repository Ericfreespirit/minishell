/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:47:16 by ladawi            #+#    #+#             */
/*   Updated: 2021/11/22 17:42:37 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	-1 none free
	0 1st arg free
	1 2nd arg free
	2 both arg free
*/

char	*ft_strjoinfree(char *s1, char *s2, int nb)
{
	char	*str;
	char	*to_free1;
	char	*to_free2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s1));
	else if (s2 == NULL)
		return (ft_strdup(s2));
	to_free1 = s1;
	to_free2 = s2;
	str = ft_strjoin(s1, s2);
	if (str == NULL)
		return (NULL);
	if (*to_free1 && (nb == 0 || nb == 2) && nb != -1)
		free(to_free1);
	if (*to_free2 && (nb == 1 || nb == 2) && nb != -1)
		free(to_free2);
	return (str);
}

char	*ft_null_strjoin(char *dest, char *src)
{
	dest = ft_strdup(src);
	free(src);
	src = NULL;
	return (dest);
}

void	ft_free_null(char **to_free1, char **to_free2, int nb)
{
	if (*to_free1 && (nb == 0 || nb == 2) && nb != -1)
	{
		free(*to_free1);
		*to_free1 = NULL;
	}
	if (*to_free2 && (nb == 1 || nb == 2) && nb != -1)
	{
		free(*to_free2);
		*to_free2 = NULL;
	}
}

char	*ft_strjoinfree2(char **s1, char **s2, int nb)
{
	char	*str;
	char	**to_free1;
	char	**to_free2;

	if (*s1 == NULL && s2 == NULL)
		return (NULL);
	else if (*s1 == NULL)
		return (ft_null_strjoin(*s1, *s2));
	else if (*s2 == NULL)
		return (ft_null_strjoin(*s2, *s1));
	to_free1 = s1;
	to_free2 = s2;
	str = ft_strjoin(*s1, *s2);
	if (str == NULL)
		return (NULL);
	ft_free_null(to_free1, to_free2, nb);
	return (str);
}
