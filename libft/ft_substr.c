/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:02:27 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 17:30:08 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ss;
	unsigned int	i;
	int				len_s;

	i = 0;
	if (len <= 0)
		return (ft_strdup(""));
	ss = malloc(sizeof(*ss) * (len + 1));
	if (!s || ss == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	while (len_s > start && i < len)
		ss[i++] = s[start++];
	ss[i] = '\0';
	return (ss);
}
