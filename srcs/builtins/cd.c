/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 11:33:43 by eriling           #+#    #+#             */
/*   Updated: 2021/11/29 16:23:58 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char ***envp, char *oldpwd)
{
	char	s[MAX_PATH];
	char	*path;

	path = getcwd(s, MAX_PATH);
	export("OLDPWD", oldpwd, EQUAL, envp);
	export ("PWD", path, EQUAL, envp);
}

int	ft_cwd_onearg(char **arg, char *home, int cwd)
{
	char	*path;
	struct stat buff;

	//check path exist
	
	// printf("[%lu]\n", buff.st_dev);
	if(stat(arg[1], &buff) == -1 || buff.st_dev == 0)
		return (-7);
	if (*(arg[1]) == '~')
	{
		if (home == NULL)
			return (-2);
		path = ft_strjoin(home, &(arg[1][1]));
		cwd = chdir(path);
		free(path);
	}
	else
		cwd = chdir(arg[1]);
	return (cwd);
}

int	ft_cwd(char **arg, char ***envp)
{
	char	*home;
	int		cwd;
	int		i;

	i = 0;
	cwd = -1;
	while (arg[i])
		i++;
	home = get_varname_val("HOME", *envp);
	if (i == 1 && home == NULL)
		sg()->ret_exit = 1;
	else if (i == 1 && home != NULL)
	{
		cwd = chdir(home);
	}
	else if (i == 2)
		cwd = ft_cwd_onearg(arg, home, cwd);
	else if (i > 2)
	{
		sg()->ret_exit = 1;
		cwd = -2;
	}
	return (cwd);
}

int	ft_arr_strlen(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	cd(char **arg, char ***envp)
{
	char	s[MAX_PATH];
	char	*oldpwd;
	int		ret;

	oldpwd = getcwd(s, MAX_PATH);
	ret = ft_cwd(arg, envp);
	if (ret == 0)
	{
		if (oldpwd == NULL && ft_arr_strlen(arg) == 2
			&& ft_strcmp(arg[1], ".") == 0)
		{
			ft_putendl_fd("minishell: getcwd: no path", STDERR);
			sg()->ret_exit = 0;
			return (0);
		}
		update_pwd(envp, oldpwd);
		return (0);
	}
	else if (ret == -1)
		err_msg(strerror(errno), 2, 1);
	else if (ret == -2)
		err_msg("cd: string not in pwd", 2, 1);
	else if(ret == -7)
		err_msg("erreur de détermination du répertoire actuel", 2, 0);
	return (1);
}
