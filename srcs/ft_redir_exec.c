/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:35:34 by suchua            #+#    #+#             */
/*   Updated: 2023/04/17 02:17:01 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_cat(char *cat)
{
	return (ft_split(cat, 32));
}

static void	combine_infile(t_shell *info)
{
	t_redirlst	*tmpin;
	pid_t		id;

	tmpin = info->infile;
	while (tmpin)
	{
		id = fork();
		if (id == 0)
		{
			dup2(tmpin->fd, 0);
			dup2(info->fd[1], 1);
			close(info->fd[1]);
			close(info->fd[0]);
			execve(get_cmd_path("cat"), get_cat("cat"), info->ms_env);
			exit(127);
		}
		tmpin = tmpin->next;
	}
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}

static void	to_outfile(t_shell *info, char *cmd)
{
	t_redirlst	*tmpout;
	char		**s_cmd;
	int			flag;
	
	flag = 0;
	s_cmd = ft_split(cmd, 32);
	if (!s_cmd[0][0])
	{
		flag = 1;
		free(s_cmd[0]);
		s_cmd[0] = ft_strdup("cat");
	}
	tmpout = info->outfile;
	while (tmpout)
	{
		if (info->prevfd != -1)
			dup2(info->prevfd, 0);
		dup2(tmpout->fd, 1);
		close(info->fd[0]);
		close(info->fd[1]);
		if (fork() == 0)
		{
			if (flag)
				execve(get_cmd_path("cat"), s_cmd, info->ms_env);
			else
				execve(get_cmd_path(s_cmd[0]), s_cmd, info->ms_env);
		}
		tmpout = tmpout->next;
	}
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}

void	ft_redir_exec(t_shell *info, t_cmdlst *node)
{
	if (pipe(info->fd) == -1)
	{
		perror("minishell : pipe");
		return ;
	}
	if (info->infile)
	{
		combine_infile(info);
		info->prevfd = info->fd[0];
	}
	if (pipe(info->fd) == -1)
	{
		perror("minishell : pipe");
		return ;
	}
	if (info->outfile)
	{
		to_outfile(info, node->cmd);
		info->prevfd = info->fd[0];
	}
}
