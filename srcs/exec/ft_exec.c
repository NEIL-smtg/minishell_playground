/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:45:04 by suchua            #+#    #+#             */
/*   Updated: 2023/09/23 05:59:31 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec(t_cmdlst *node, t_shell *info)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(node->cmd, 32);
	path = get_cmd_path(s_cmd[0], info->ms_env);
	if (info->prevfd != -1 && node->prev && ft_strncmp(node->prev->cmd, ";", 2))
		dup2(info->prevfd, 0);
	if (node->next && !ft_strncmp(node->next->cmd, "|", 2))
		dup2(info->fd[1], 1);
	close(info->fd[1]);
	close(info->fd[0]);
	if (!is_builtin(s_cmd, info, node->cmd))
		execve(path, s_cmd, info->ms_env);
	free(path);
	exit(127);
}

static int	skip_permission(t_shell *info, t_cmdlst **node)
{
	int		flag;

	flag = 0;
	if (!ft_strncmp((*node)->cmd, "|", 2))
		flag = 1;
	else if (!ft_strncmp((*node)->cmd, ";", 2))
		flag = 1;
	else if (set_redir(info, node) || parent_exec(info, *node))
		flag = 1;
	if (flag)
		(*node) = (*node)->next;
	return (flag);
}

static int	exec_pipe(t_shell *info, t_cmdlst **node)
{
	pid_t		id;

	while ((*node) && !is_doubles((*node)->cmd))
	{
		if (pipe(info->fd) == -1)
			return (0);
		if (skip_permission(info, node))
			continue ;
		ft_parse_input(info, node);
		id = fork();
		if (id == 0)
			ft_exec(*node, info);
		else if (id == -1)
			return (0);
		close(info->fd[1]);
		if (info->prevfd != -1)
			close(info->prevfd);
		info->prevfd = info->fd[0];
		(*node) = (*node)->next;
	}
	return (1);
}

void	ft_cmdexec(t_shell *info)
{
	t_cmdlst	*tmp;

	tmp = info->cmdlst;
	while (tmp)
	{
		info->prevfd = -1;
		if (!exec_pipe(info, &tmp))
			return ;
		close(info->prevfd);
		wait_child_process(info);
		if (info->ms_status)
			cmd_not_found(info->cmdlst, info);
		if (!tmp || (!ft_strncmp(tmp->cmd, "&&", 3) && info->ms_status))
			break ;
		if (!info->ms_status && !ft_strncmp(tmp->cmd, "||", 3))
			skip_cmd_decider(&tmp);
		tmp = tmp->next;
	}
	wait_child_process(info);
}
