/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 23:36:16 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 19:51:22 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_output(t_shell *info, int piping, char *cmd)
{
	char	**s_cmd;

	s_cmd = ft_split(cmd, 32);
	if (piping)
	{
		dup2(info->fd[1], 1);
		close(info->fd[0]);
		close(info->fd[1]);
	}
	if (info->prevfd != -1)
		dup2(info->prevfd, 0);
	if (!is_builtin(s_cmd, info, cmd))
		execve(get_cmd_path(s_cmd[0]), s_cmd, info->ms_env);
	exit(127);
}

void	shell_output(int piping, t_shell *info, char *cmd)
{
	pid_t	id;

	if (piping && pipe(info->fd) == -1)
		return ;
	id = fork();
	if (id == -1)
		return ;
	if (id == 0)
		child_output(info, piping, cmd);
	close(info->fd[1]);
	if (piping)
		info->prevfd = info->fd[0];
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}
