/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:45:04 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 18:54:14 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_bonus(char *s)
{
	if (!ft_strncmp(s, "||", 3) || !ft_strncmp(s, "&&", 3))
		return (1);
	return (0);
}

static void	ft_exec(t_cmdlst *node, t_shell *info)
{
	char	**s_cmd;

	s_cmd = ft_split(node->cmd, 32);
	if (info->prevfd != -1 && node->prev && ft_strncmp(node->prev->cmd, ";", 2))
		dup2(info->prevfd, 0);
	if (node->next && !ft_strncmp(node->next->cmd, "|", 2))
		dup2(info->fd[1], 1);
	close(info->fd[1]);
	close(info->fd[0]);
	execve(get_cmd_path(s_cmd[0]), s_cmd, info->ms_env);
	exit(127);
}

void	ft_cmdexec(t_shell *info)
{
	pid_t		id;
	t_cmdlst	*tmp;
	
	tmp = info->cmdlst;
	while (tmp)
	{
		info->prevfd = -1;
		while (tmp && !is_bonus(tmp->cmd))
		{
			if (pipe(info->fd) == -1)
				return ;
			if (!ft_strncmp(tmp->cmd, "|", 2) || !ft_strncmp(tmp->cmd, ";", 2)
					|| set_redir(info, &tmp))
			{
				tmp = tmp->next;
				continue ;
			}
			id = fork();
			if (id == 0)
				ft_exec(tmp, info);
			close(info->fd[1]);
			if (info->prevfd != -1)
				close(info->prevfd);
			info->prevfd = info->fd[0];
			tmp = tmp->next;
		}
		close(info->prevfd);
		while (waitpid(-1, &info->ms_status, 0) > 0)
			continue ;
		if (info->ms_status)
			perror("minishell");
		if (!tmp || (!ft_strncmp(tmp->cmd, "&&", 3) && info->ms_status))
			break ;
		if (!info->ms_status && !ft_strncmp(tmp->cmd, "||", 3))
			while (tmp->next && !is_bonus(tmp->next->cmd))
				tmp = tmp->next;
		tmp = tmp->next;
	}
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}
