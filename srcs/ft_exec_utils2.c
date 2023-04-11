/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:55:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/20 19:45:18 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(char **s_cmd, t_shell *info)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (s_cmd[++i])
	{
		waitpid(0, &info->ms_status, 0);
		if (info->ms_status && !flag)
		{
			msg_cmd_not_found(ft_split(s_cmd[0], 32));
			flag = 1;
		}
	}
}

int	is_builtin_cmd(char **cmd, t_shell *info)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(info, cmd);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		exit(EXIT_SUCCESS);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		ft_cd(info, cmd);
	else if (!ft_strncmp(cmd[0], "export", 7))
		ft_export(info, cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd(info);
	else if (!ft_strncmp(cmd[0], "env", 4))
		ft_env(info);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(info, cmd);
	else
		return (0);
	return (1);
}

void	close_infile_outfile(t_shell *info)
{
	if (info->infile != -1)
		close(info->infile);
	if (info->outfile != -1)
		close(info->outfile);
	info->infile = -1;
	info->outfile = -1;
}

void	close_all_pipe(t_shell *info, int n_pipe, int type)
{
	int	i;

	if (n_pipe < 1)
		return ;
	i = -1;
	close_infile_outfile(info);
	while (++i < n_pipe)
	{
		close(info->fd[i][1]);
		close(info->fd[i][0]);
		if (type == FREE_PIPE)
			free(info->fd[i]);
	}
	if (type == FREE_PIPE)
		free(info->fd);
}
