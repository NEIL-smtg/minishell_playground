/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:46:42 by suchua            #+#    #+#             */
/*   Updated: 2023/05/17 15:15:57 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_redirlst(char *filename, t_shell *info, int type)
{
	int	fd;

	if (type == L1)
		fd = open(filename, O_RDONLY);
	else if (type == R2)
		fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0000644);
	else
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0000644);
	if (fd == -1)
	{
		perror(filename);
		info->open_error = -1;
		free(filename);
		return ;
	}
	if (type == L1)
		redirlst_addback(&info->infile, filename, fd);
	else if (type == R2 || type == R1)
		redirlst_addback(&info->outfile, filename, fd);
	free(filename);
}

static void	trim_cmd(t_cmdlst **node, int sq, int dq, int flag)
{
	int	i;

	i = -1;
	while ((*node)->cmd[++i])
	{
		if ((*node)->cmd[i] == 34)
			dq = !dq;
		else if ((*node)->cmd[i] == 39)
			sq = !sq;
		if (((*node)->cmd[i] == '<' || (*node)->cmd[i] == '>') && !dq && !sq)
		{
			(*node)->cmd[i] = 32;
			flag = 1;
			continue ;
		}
		while (flag && (*node)->cmd[i] && ft_isspace((*node)->cmd[i]))
			++i;
		while (flag && (*node)->cmd[i] && !ft_isspace((*node)->cmd[i]))
		{
			(*node)->cmd[i] = 32;
			++i;
		}
		flag = 0;
	}
}

static int	redir_decider(t_shell *info, t_cmdlst **node)
{
	if (!info->infile && !info->outfile)
		return (0);
	trim_cmd(node, 0, 0, 0);
	ft_parse_input(info, node);
	ft_redir_exec(info, *node);
	ft_free_infile_outfile(info);
	return (1);
}

static void	scan_redir(t_shell *info, t_cmdlst **node, int dq, int sq)
{
	t_cmdlst	*tmp;
	int			i;

	i = -1;
	tmp = *node;
	while (tmp->cmd[++i])
	{
		if (tmp->cmd[i] == 34)
			dq = !dq;
		else if (tmp->cmd[i] == 39)
			sq = !sq;
		else if (!ft_strncmp("<<", &(tmp->cmd[i]), 2) && !dq && !sq)
			heredoc(get_limiter(&tmp->cmd[i + 2]), info, tmp->next);
		else if (tmp->cmd[i] == '<' && !dq && !sq)
			build_redirlst(get_limiter(&tmp->cmd[i + 1]), info, L1);
		else if (!ft_strncmp(">>", &(tmp->cmd[i]), 2) && !dq && !sq)
			build_redirlst(get_limiter(&tmp->cmd[i + 2]), info, R2);
		else if (tmp->cmd[i] == '>' && !dq && !sq)
			build_redirlst(get_limiter(&tmp->cmd[i + 1]), info, R1);
		if (info->open_error == -1)
			return ;
		if (!ft_strncmp("<<", &(tmp->cmd[i]), 2)
			|| !ft_strncmp(">>", &(tmp->cmd[i]), 2))
			++i;
	}
}

int	set_redir(t_shell *info, t_cmdlst **node)
{
	info->infile = NULL;
	info->outfile = NULL;
	scan_redir(info, node, 0, 0);
	return (redir_decider(info, node));
}
