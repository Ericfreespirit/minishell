/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:37:21 by eriling           #+#    #+#             */
/*   Updated: 2021/11/28 20:47:09 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_ast *node, char *cmd)
{
	if (node && cmd != 0)
	{
		if ((ft_strcmp(cmd, "cd")) == 0)
		{
			cd(node->arg, &sg()->env);
		}
		else if ((ft_strcmp(cmd, "export")) == 0)
			launch_export(node->arg, &sg()->env);
		else if ((ft_strcmp(cmd, "unset")) == 0)
			launch_unset(node->arg, &sg()->env);
		else if ((ft_strcmp(cmd, "exit")) == 0)
			ft_exit(node);
		else if ((ft_strcmp(cmd, "pwd")) == 0)
			pwd();
		else if ((ft_strcmp(cmd, "echo")) == 0)
			echo(node->arg);
		else if ((ft_strcmp(cmd, "env")) == 0)
			env(sg()->env);
		else
			fork_execve(node);
	}
	return (0);
}

/*
	Execute two node command in pipe node
*/
void	exec_pipe(t_ast *node)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close (pipefd[0]);
		dup2(pipefd[1], 1);
		exec_ast(node->left);
		close(pipefd[1]);
		free_exit(0, 0);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		exec_ast(node->right);
		close(pipefd[0]);
		pid = waitpid(0, &sg()->chd_status, 0);
	}
}

/*
	Execute ast recursively
*/
int	exec_ast(t_ast *node)
{	
	if (node->left == NULL && node->right == NULL)
	{
		if (node->redir != NULL)
		{
			if (exec_redir(node->redir) == -1)
			{
				return (-1);
			}
		}
		if (node->arg == NULL
			|| exec_command(node, node->arg[0]) == -1)
			return (-1);
	}
	else if ((node->left != 0 && node->left->arg != 0)
		&& (node->right != 0 && node->right->arg != 0)
		&& ft_strcmp(node->arg[0], "|") == 0)
		exec_pipe(node);
	close(0);
	close(1);
	return (0);
}
