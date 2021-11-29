/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 12:24:55 by eriling           #+#    #+#             */
/*   Updated: 2021/11/29 14:52:27 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

void	handler_sigchild(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = wait(&status);
	if (pid == -1)
		return ;
}

void	handler_sigint(int sig)
{
	if (sig == 2)
	{
		sg()->ret_exit = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		if (sg()->in_hdoc == 0)
		{
			write(1, "\n", 1);
			rl_redisplay();
		}
		else if (sg()->in_hdoc == 1)
		{
			write(1, "\n", 1);
			free_exit(130, 0);
		}
	}
}

void	handler_sigquit(int sig)
{
	int	status;
	int	tmp;

	(void)sig;
	tmp = waitpid(sg()->lst_pid, &status, WUNTRACED);
	if (tmp == -1)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	write(1, "Quit: (core dumped)\n", 21);
	rl_redisplay();
	sg()->quit = 1;
	sg()->ret_exit = 131;
}

void	ctrl_d(void)
{
	int	status;

	write(1, "exit\n", 5);
	status = sg()->ret_exit;
	free_program();
	exit(status);
}
