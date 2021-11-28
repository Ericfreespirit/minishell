/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:45:51 by ladawi            #+#    #+#             */
/*   Updated: 2021/07/22 19:25:37 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*new_ptr;
	void	*tmp;

	if (ptr == NULL)
	{
		tmp = ft_calloc(1, size);
		if (tmp == NULL)
			return (NULL);
		return (tmp);
	}
	if (!size)
		return (ptr);
	new_ptr = ft_calloc(1, size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
