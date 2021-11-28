/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 17:14:31 by eriling           #+#    #+#             */
/*   Updated: 2021/08/18 14:57:38 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*sg(void)
{
	static t_data	*all = NULL;

	if (all)
		return (all);
	all = ft_calloc(sizeof(t_data), 1);
	return (all);
}
