/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 12:24:55 by eriling           #+#    #+#             */
/*   Updated: 2021/11/28 19:44:24 by eriling          ###   ########.fr       */
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
	(void)sig;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	ctrl_d(void)
{
	write(1, "exit\n", 5);
	free_program();
	exit(0);
}

void	ft_signal_ignored(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGCHLD, NULL);
}