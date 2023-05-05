/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:47:17 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 19:50:57 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!is_builtin(s_cmd, info, cmd))
		execve(get_cmd_path(s_cmd[0]), s_cmd, info->ms_env);
	exit(127);
}

static void	redirecting(t_shell *info, char *cmd, int piping)
{
	t_redirlst	*tmpout;
	int			flag;
	pid_t		id;

	tmpout = info->outfile;
	flag = 0;
	while (tmpout)
	{
		id = fork();
		if (id == 0)
			redirect_child_process(flag, info, tmpout, cmd);
		else if (id == -1)
			return ;
		waitpid(-1, &info->ms_status, 0);
		if (info->ms_status)
			return ;
		flag = 1;
		close(info->prevfd);
		close(tmpout->fd);
		info->prevfd = open(tmpout->filename, O_RDONLY);
		if (!tmpout->next && piping)
			break ;
		tmpout = tmpout->next;
	}
}

void	redirect_output(int piping, t_shell *info, char *cmd)
{
	redirecting(info, cmd, piping);
	if (!piping)
	{
		close(info->prevfd);
		info->prevfd = -1;
	}
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}
