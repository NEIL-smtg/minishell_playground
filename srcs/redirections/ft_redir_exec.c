/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:35:34 by suchua            #+#    #+#             */
/*   Updated: 2023/05/15 18:04:56 by suchua           ###   ########.fr       */
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
			execve(get_cmd_path("cat", info->ms_env),
				ft_split("cat ", 32), info->ms_env);
			exit(127);
		}
		tmpin = tmpin->next;
	}
	close(info->fd[1]);
	info->prevfd = info->fd[0];
	wait_child_process(info);
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
