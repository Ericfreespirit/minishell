/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:05:25 by eriling           #+#    #+#             */
/*   Updated: 2021/11/29 14:52:47 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_ast(void)
{
	int	std_out;
	int	std_in;

	std_out = dup(1);
	std_in = dup(0);
	if (get_tree() == 0)
	{
		if (check_ast(sg()->node) == 0)
		{
			hdoc_backtracking(sg()->node);
			if (sg()->stop != 1)
				exec_ast(sg()->node);
		}
		free_ast(sg()->node, 0);
		dup2(std_out, 1);
		dup2(std_in, 0);
	}
	else
	{
		free_ast(sg()->node, 0);
		return (1);
	}
	return (0);
}

void	readline_gnl(void)
{
	char	*line;
	char	*save;
	int		status;

	status = 0;
	while (get_next_line(0, &line, 1) != 0)
		save = line;
	if (save == NULL)
		ctrl_d();
	if (get_lexical_field(save) == 1)
		return (err_msg("Error syntax", 2, 1));
	sg()->tmp = sg()->lex_fi;
	if (*save != '\0' && launch_ast() == -1)
		free_line_exit(save);
	free_lexical_field(sg()->tmp, 0);
	status = sg()->ret_exit;
	free_program();
	exit(status);
}

void	ft_signal(void)
{
	signal(SIGINT, &handler_sigint);
	signal(SIGQUIT, &handler_sigquit);
	signal(SIGCHLD, &handler_sigchild);
	sg()->quit = 0;
}

void	ft_readline(char **line)
{
	*line = readline(sg()->prompt);
	add_history(*line);
	rl_redisplay();
	sg()->lst_pid = 0;
}

void	launch_minishell(void)
{
	char	*line;

	while (1)
	{
		ft_signal();
		if (isatty(0))
		{
			ft_readline(&line);
			if (line == NULL)
				ctrl_d();
			if (get_lexical_field(line) == 1)
			{	
				free(line);
				return (err_msg("Error syntax", 2, 1));
			}
			sg()->tmp = sg()->lex_fi;
			sg()->stop = 0;
			if (*line != '\0' && launch_ast() == -1)
				free_line_exit(line);
			free_lexical_field(sg()->tmp, 0);
		}
		else
			readline_gnl();
		free(line);
	}
}
