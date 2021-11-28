/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdl_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:24:19 by eriling           #+#    #+#             */
/*   Updated: 2021/11/22 13:32:31 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_hdoc(char *str)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		free_exit(0, 3);
	write(pfd[1], str, ft_strlen(str));
	close(pfd[1]);
	return (pfd[0]);
}

char	*rdl_hdoc(t_hdoc *hdoc)
{
	char	*line;

	sg()->in_hdoc = 1;
	line = readline("> ");
	if (line == NULL)
		return (str_error2("bash: warning: << here-document >>", NULL, 0));
	while (ft_strcmp(line, hdoc->end))
	{
		if (sg()->str == NULL)
			sg()->str = ft_strdup(line);
		else
			(sg()->str) = ft_strjoinfree(sg()->str, line, 0);
		(sg()->str) = ft_strjoinfree(sg()->str, "\n", 0);
		free(line);
		line = readline("> ");
		if (line == NULL)
			return (str_error2("bash: warning: << here-document >>",
					sg()->str, 0));
	}
	sg()->in_hdoc = 0;
	free(line);
	if (hdoc->next == NULL)
		return (sg()->str);
	return (free_rdl_str());
}

void	fork_chd_rdl_hdoc(int *pfd, t_hdoc *hdoc)
{
	int		hdoc_fd;
	char	*buf;
	char	*hdoc_inp;
	t_hdoc	*tmp;

	tmp = hdoc;
	while (tmp != NULL)
	{
		hdoc_inp = rdl_hdoc(tmp);
		if (hdoc_inp != NULL)
		{
			close(pfd[0]);
			hdoc_fd = read_hdoc(hdoc_inp);
			buf = ft_calloc(2, sizeof(char *));
			if (buf == NULL)
				return ;
			while (read(hdoc_fd, buf, 1))
				write(pfd[1], buf, ft_strlen(buf));
			free(buf);
			close(hdoc_fd);
			close(pfd[1]);
		}
		tmp = tmp->next;
	}
	free_exit(0, 0);
}

int	fork_par_rdl_hdoc(int *pfd, pid_t pid, t_ast *node)
{
	int		status;

	status = 0;
	pid = wait(&status);
	close(pfd[1]);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) == 130)
			return (1);
	add_fd_redir(node, pfd[0]);
	return (0);
}

int	fork_rdl_hdoc(t_ast *node)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (sg()->stop == 1 || node->hdoc == NULL || pipe(pfd) == 1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid > 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		if (fork_par_rdl_hdoc(pfd, pid, node) == 1)
			return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, &handler_sigint);
		fork_chd_rdl_hdoc(pfd, node->hdoc);
	}
	return (0);
}
