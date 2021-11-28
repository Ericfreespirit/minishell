/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:55:10 by eriling           #+#    #+#             */
/*   Updated: 2021/11/28 23:19:28 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	parsing_launch_exec(char **envp, char ***arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (to_find_varname(envp[i], "PATH"))
		{
			*arr = ft_split(&envp[i][5], ':');
			while ((*arr)[j])
			{
				tmp = ft_strdup("/");
				(*arr)[j] = ft_strjoinfree2(&((*arr)[j]), &tmp, 2);
				j++;
			}
			return (0);
		}
		i++;
	}
	err_msg("minishell : can't found $PATH in env", 2, 1);
	return (1);
}

int	found_str(char *src, char *str, char **arr, char **arg)
{
	int	i;

	i = 0;
	while (src[i] && src[i] == str[i])
		i++;
	if (str[i] == 0)
	{
		if (execve(arg[0], arg, sg()->env) == -1)
		{
			free_arg(arr);
			ft_putstr_fd("command not found\n", 2);
			free_exit(127, 0);
		}
	}
	return (1);
}

void	ft_execve(char **arg, char **envp)
{
	char	**arr;
	char	*tmp;
	int		i;

	i = 0;
	arr = NULL;
	found_str(arg[0], "/bin/", arr, arg);
	found_str(arg[0], "./", arr, arg);
	if (parsing_launch_exec(envp, &arr) == 1)
		free_exit(127, 0);
	while (arr[i])
	{
		tmp = arr[i];
		arr[i] = ft_strjoin(arr[i], *arg);
		free(tmp);
		execve(arr[i], arg, envp);
		i++;
	}
	free_arg(arr);
	ft_putstr_fd("command not found\n", 1);
	free_exit(127, 0);
}

/*
	Return value of the signal in child process
*/
void	child_status(int status)
{
	if (status == 2)
	{
		write(1, "\n", 1);
		sg()->ret_exit = 130;
	}
	else if (status == 131 || sg()->quit == 1)
		sg()->ret_exit = 131;
	else if (status == 0)
		sg()->ret_exit = 0;

}

void	fork_execve(t_ast *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (err_msg("Error fork", 2, 1));
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGCHLD, NULL);
		pid = waitpid(0, &status, 0);
		if (pid == -1)
			return ;
		int ret;
	 if (WIFSIGNALED(status))
	{
			ret = WTERMSIG(status);
			sg()->ret_exit = WTERMSIG(status);
	}
	else if (WIFEXITED(status))
	{
		ret = WEXITSTATUS(status);
		sg()->ret_exit = WEXITSTATUS(status);
	}
		child_status(status);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_execve(node->arg, sg()->env);
	}
}
