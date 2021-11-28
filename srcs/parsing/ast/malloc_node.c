/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:36:58 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:39:55 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Realloc arg in node (arg is all element of a command)
	Add str in arg
*/
char	**realloc_node_arg(char **arg, char *str)
{
	int		len;
	int		i;
	char	**arr;

	i = 0;
	len = len_arr(arg);
	arr = ft_calloc(sizeof(char *), len + 2);
	if (arr == NULL)
		return (free_arg(arg));
	while (arg[i])
	{
		arr[i] = ft_strdup(arg[i]);
		if (arr[i] == NULL)
			return (free_arg_arr(arg, arr));
		i++;
	}
	free_arg(arg);
	arr[len] = str;
	return (arr);
}

/*
	Store redirection
*/
t_redir	*store_redir(char *str)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	if (!ft_strcmp(str, "<"))
		new->index = 1;
	else if (!ft_strcmp(str, ">"))
		new->index = 2;
	else if (!ft_strcmp(str, "<<"))
		new->index = 3;
	else if (!ft_strcmp(str, ">>"))
		new->index = 4;
	else
		new->index = 0;
	new->file = NULL;
	new->hdoc_fd = -1;
	new->next = NULL;
	return (new);
}
