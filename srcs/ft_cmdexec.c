/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:45:04 by suchua            #+#    #+#             */
/*   Updated: 2023/04/13 02:29:07 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_bonus(char *s)
{
	if (!ft_strncmp(s, "||", 3) || !ft_strncmp(s, "&&", 3))
		return (1);
	return (0);
}

static void	ft_exec(t_cmdlst *node, int fd[2], int prevfd, t_shell *info)
{
	char	**s_cmd;
	char	*cmd_path;
	t_cmdlst	*tmp;
	char	*new;

	s_cmd = ft_split(node->cmd, 32);
	if (prevfd != -1)
		dup2(prevfd, 0);
	if (node->next && !ft_strncmp(node->next->cmd, "|", 2))
		dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	cmd_path = get_cmd_path(s_cmd[0]);
	tmp = node;
	if (!cmd_path && tmp->prev && !(ft_strncmp("&&", tmp->prev->cmd, 3)))
	{
		if (!tmp->prev || !tmp->prev->prev)
			exit(127);
		tmp = tmp->prev->prev;
		new = ft_strjoin(tmp->cmd, " -");
		new = gnl_strjoin(new, node->cmd);
		ft_free2d(s_cmd);
		free(cmd_path);
		free(node->cmd);
		node->cmd = new;
		s_cmd = ft_split(node->cmd, 32);
		cmd_path = get_cmd_path(s_cmd[0]);
	}
	execve(cmd_path, s_cmd, info->ms_env);
	exit(127);
}

void	ft_cmdexec(t_shell *info)
{
	int			fd[2];
	pid_t		id;
	t_cmdlst	*tmp;
	int			prevfd;
	
	tmp = info->cmdlst;
	prevfd = -1;
	while (tmp)
	{
		while (tmp && !is_bonus(tmp->cmd))
		{
			if (!ft_strncmp(tmp->cmd, "|", 2))
			{
				tmp = tmp->next;
				continue ;
			}
			if (pipe(fd) == -1)
				return ;
			id = fork();
			if (id == 0)
				ft_exec(tmp, fd, prevfd, info);
			close(fd[1]);
			if (prevfd != -1)
				close(prevfd);
			prevfd = fd[0];
			tmp = tmp->next;
		}
		close(prevfd);
		while (waitpid(-1, &info->ms_status, 0) > 0)
			continue ;
		if (info->ms_status)
			perror("Command not found");
		if (!tmp || (!ft_strncmp(tmp->cmd, "&&", 3) && info->ms_status))
			break ;
		tmp = tmp->next;
	}
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}
