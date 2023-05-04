/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:35:34 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 00:14:54 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			close(tmpin->fd);
			execve(get_cmd_path("cat"), ft_split("cat ", 32), info->ms_env);
			exit(127);
		}
		tmpin = tmpin->next;
	}
	close(info->fd[1]);
	info->prevfd = info->fd[0];
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}

static void	redirect_child_process(int flag, t_shell *info,
	t_redirlst *tmpout, char *cmd)
{
	char	**s_cmd;

	if (!flag)
		s_cmd = ft_split(cmd, 32);
	else
		s_cmd = ft_split("cat ", 32);
	if (info->prevfd != -1)
		dup2(info->prevfd, 0);
	dup2(tmpout->fd, 1);
	close(tmpout->fd);
	if (info->prevfd != -1)
		close(info->prevfd);
	execve(get_cmd_path(s_cmd[0]), s_cmd, info->ms_env);
	exit(127);
}

void	redirect_output(int piping, t_shell *info, char *cmd)
{
	t_redirlst	*tmpout;
	int			flag;

	tmpout = info->outfile;
	flag = 0;
	while (tmpout)
	{
		if (fork() == 0)
			redirect_child_process(flag, info, tmpout, cmd);
		waitpid(-1, &info->ms_status, 0);
		flag = 1;
		close(info->prevfd);
		close(tmpout->fd);
		info->prevfd = open(tmpout->filename, O_RDONLY);
		if (!tmpout->next && piping)
			break ;
		tmpout = tmpout->next;
	}
	if (!piping)
	{
		close(info->prevfd);
		info->prevfd = -1;
	}
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}

void	ft_redir_exec(t_shell *info, t_cmdlst *node)
{
	int		piping;
	size_t	i;

	if (info->infile)
	{
		info->prevfd = -1;
		combine_infile(info);
	}
	piping = 0;
	if (node->next && !ft_strncmp(node->next->cmd, "|", 2))
		piping = 1;
	i = 0;
	while (node->cmd[i] && ft_isspace(node->cmd[i]))
		++i;
	if (i == ft_strlen(node->cmd) && info->outfile)
		redirect_output(piping, info, "cat ");
	else if (i != ft_strlen(node->cmd) && info->outfile)
		redirect_output(piping, info, node->cmd);
	else if (i == ft_strlen(node->cmd))
		shell_output(piping, info, "cat ");
	else if (i != ft_strlen(node->cmd))
		shell_output(piping, info, node->cmd);
}
