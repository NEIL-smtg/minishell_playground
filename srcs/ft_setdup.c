/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:49:01 by suchua            #+#    #+#             */
/*   Updated: 2023/03/21 16:52:45 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_no_pipe_dup(t_shell *info)
{
	if (info->infile == -1 && info->outfile == -1)
		return ;
	if (info->infile != -1)
	{
		dup2(info->infile, 0);
		close(info->infile);
		info->infile = -1;
	}
	if (info->outfile != -1)
	{
		dup2(info->outfile, 1);
		close(info->outfile);
		info->outfile = -1;
	}
}	

static void	set_first_cmd_dup(t_shell *info)
{
	if (info->infile != -1)
		dup2(info->infile, 0);
	if (info->outfile != -1)
	{
		dup2(info->outfile, 1);
		// dup2(info->fd[0][1], 1);
	}
	else
		dup2(info->fd[0][1], 1);
}

static void	set_last_cmd_dup(t_shell *info, int index)
{
	if (info->infile != -1)
		dup2(info->infile, 0);
	else
		dup2(info->fd[index - 1][0], 0);
	if (info->outfile != -1)
		dup2(info->outfile, 1);
}

static void	set_middle_cmd_dup(t_shell *info, int index)
{
	if (info->infile != -1)
	{
		dup2(info->infile, 0);
		// dup2(info->fd[index][0], info->infile);
	}
	else
		dup2(info->fd[index - 1][0], 0);
	if (info->outfile != -1)
	{
		dup2(info->outfile, 1);
		// dup2(info->fd[index][1], info->outfile);
	}
	else
		dup2(info->fd[index][1], 1);
}

void	set_dup(t_shell *info, char *nxt_cmd, int index)
{
	if (nxt_cmd && index == 0)
		set_first_cmd_dup(info);
	else if (!nxt_cmd)
		set_last_cmd_dup(info, index);
	else
		set_middle_cmd_dup(info, index);
}
